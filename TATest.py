#!/usr/bin/env python3
"""Script to perform end-to-end tests on the examples"""

import difflib
import gzip
import optparse
import os
import re
import subprocess
import sys

# These paths are relative to the directory in which this script is stored.
# We make sure we are in the appropriate directory in the __main__ at the
# bottom of this file.
EXECUTABLE = os.path.join("pes.timed", "timesolver-ta")


def filterTimes(lines):
    """Filter times from the output. This data is variable, so should not be
       taken into account in the comparison."""
    invalid = re.compile(r"(running|Program|start|end) (t|T)(ime)|demo|timesolver")
    return list(filter(lambda x: invalid.search(x) is None, lines))


def compare(expectedFileName, given, printDiff = False):
    """Compare the output in the file with name expectedFileName to the
    string given"""
    try:
        with gzip.open(expectedFileName, 'rt') as f:
            expectedFile = filterTimes(f.readlines())
            givenLines = filterTimes(given.splitlines(keepends=True))

            result = expectedFile == givenLines
            if(printDiff and not result):
                sys.stdout.write("[!!!] Output has changed for {0}\n".format(expectedFileName))
                sys.stdout.write("[!!!] Diff follows")
                d = difflib.Differ()
                diff = d.compare(expectedFile, givenLines)
                sys.stdout.writelines(diff)
            return result
    except:
        sys.stdout.write("[!!!] Failed to compare with existing file {0}\n".format(expectedFileName))
        return False


def runTestCase(dirName, fileName, overwrite, printdiff, debug, diff):
    """Run the tool 'demo' on the testcase dirName/fileName. If overwrite is
    True, the expected output is overwritten. If overwrite is False, the output
    is compared to the file in which the expected output is stored."""
    try:
        if debug:
            cmd = [EXECUTABLE, "-d", os.path.join(dirName, fileName)]
        else:
            cmd = [EXECUTABLE, os.path.join(dirName, fileName)]

        ret = subprocess.run(cmd, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             universal_newlines=True, check=True)
        resultFile = fileName + ".expectedout.gz"
        resultPath = os.path.join(dirName, resultFile)

        # Check whether the file exists. If it exists, compare the result, and
        # do not overwrite if the content is the same
        if diff:
            if overwrite:
                result = None
                if os.path.exists(resultPath):
                    result = compare(resultPath, ret.stderr)

                if result:
                    print('[{0}] {1}/{2}'.format('\033[32mKEEP\033[39m',
                          dirName, resultFile))
                else:
                    with gzip.open(os.path.join(dirName, resultFile), 'wt') as f:
                        f.write(ret.stderr)
                        print('[{0}] {1}/{2}'.format(
                              '\033[33mGENERATE\033[39m', dirName, resultFile))
            else:
                result = compare(os.path.join(dirName, resultFile), ret.stderr,
                                 printdiff)
                print('[{0}] {1}/{2}'.format('\033[32mOK\033[39m' if result
                      else '\033[31mFAILED\033[39m', dirName, fileName))
        else:
            print('[{0}] {1}/{2}'.format('\033[32mRUN\033[39m', dirName,
                                         resultFile))
            result = True
    except subprocess.CalledProcessError as e:
        print('[{0}] {1}/{2}'.format('\033[31mFAILED\033[39m', dirName,
                                     fileName))
        print('Standard out: {0}'.format(e.stdout))
        print('Standard error: {0}'.format(e.stderr))
        result = False

    return result


def traverseTestCases(rootDir, overwrite, printdiff, fileFilter, debug=True,
                      diff=True):
    """Run all test cases below rootDir. If overwrite is True, then we only use
    the current version of the executable to generate the expected output.
    if debug, then the tool will be called with the debug flag."""
    count = 0
    failed = 0
    for dirName, subdirList, fileList in os.walk(rootDir):
        for fname in fileList:
            # Skip expected output files
            if fileFilter(fname):
                continue
            count += 1
            res = runTestCase(dirName, fname, overwrite, printdiff, debug,
                              diff)
            if(not res):
                failed += 1
    print("{0} tests were run".format(count))
    print("{0} tests failed".format(failed))
    return failed


# Filter for ignoring certain files from the examples directory.
def fileFilter(fileName):
    return fileName[0] == '.' or fileName == 'Makefile' or \
        os.path.splitext(fileName)[1] in ['.gz', '.hh', '.cc']


def main():
    """
    Parse the command line, and run the experiments.
    """
    parser = optparse.OptionParser(usage='usage: %prog [options]')
    parser.add_option('-x', action='store_true', dest='examples',
                      help='Run a selection of examples')
    parser.add_option('-n', action='store_true', dest='notest',
                      help='Do not run the test cases from CorrectnessTestSuite')
    parser.add_option('-o', action='store_true', dest='overwrite',
                      help='Overwrite expected outputs')
    parser.add_option('-d', action='store_true', dest='printdiff',
                      help='Print diff in case of failed test')
    parser.add_option('--nodebug', action='store_true', dest='nodebug', default=False,
                      help='Call timesolver without the debug flag, and do not compute the diffs')
    options, args = parser.parse_args()

    curdir = os.getcwd()
    script_dir = os.path.dirname(os.path.realpath(__file__))
    os.chdir(script_dir)

    totalFailed = 0

    if not options.notest:
        testdir = os.path.join("examples", "CorrectnessTestSuite")
        print('Running all test cases in {0}'.format(testdir))
        totalFailed += traverseTestCases(testdir, options.overwrite,
                                         options.printdiff, fileFilter,
                                         not options.nodebug,
                                         not options.nodebug)

    if options.examples:
        testdir = os.path.join("examples", "FISCHER")
        print('Running all test cases in {0}'.format(testdir))
        totalFailed += traverseTestCases(testdir, options.overwrite,
                                         options.printdiff,
                                         lambda x: fileFilter(x) or not x.startswith('FISCHER-4'),
                                         not options.nodebug,
                                         not options.nodebug)

        # Do not check the full output since this gives rise to some extremely large files.
        testdir = os.path.join("examples", "GRC")
        print('Running all test cases in {0}'.format(testdir))
        totalFailed += traverseTestCases(testdir, options.overwrite,
                                         options.printdiff,
                                         lambda x: fileFilter(x) or not x.startswith('GRC-4'),
                                         False,
                                         not options.nodebug)

        testdir = os.path.join("examples", "LEADER")
        print('Running all test cases in {0}'.format(testdir))
        totalFailed += traverseTestCases(testdir, options.overwrite,
                                         options.printdiff, lambda x: fileFilter(x) or not x.startswith('LEADER-4'),
                                         not options.nodebug,
                                         not options.nodebug)

        testdir = os.path.join("examples", "TrainGate")
        print('Running all test cases in {0}'.format(testdir))
        totalFailed += traverseTestCases(testdir, options.overwrite,
                                         options.printdiff,
                                         lambda x: fileFilter(x) or (not x.startswith('Train2') and not x.startswith('Train3')),
                                         not options.nodebug,
                                         not options.nodebug)

    os.chdir(curdir)
    return totalFailed


if __name__ == "__main__":
    result = main()
    if result == 0:
        sys.exit(0)
    else:
        sys.exit(1)
