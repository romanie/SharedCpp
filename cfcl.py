#!/usr/bin/python

import argparse
import sys
import os
import httplib
import time
from subprocess import call
from HTMLParser import HTMLParser

class asciicolors:
	RESET = "\033[0m"
	BLACK = "\033[30m"
	RED = "\033[31m"
	GREEN = "\033[32m"
	YELLOW = "\033[33m"
	BLUE = "\033[34m"
	MAGENTA = "\033[35m"
	CYAN = "\033[36m"
	WHITE = "\033[37m"
	BOLDBLACK = "\033[1m\033[30m"
	BOLDRED = "\033[1m\033[31m"
	BOLDGREEN = "\033[1m\033[32m"
	BOLDYELLOW = "\033[1m\033[33m"
	BOLDBLUE = "\033[1m\033[34m"
	BOLDMAGENTA = "\033[1m\033[35m"
	BOLDCYAN = "\033[1m\033[36m"
	BOLDWHITE = "\033[1m\033[37m"

if not os.path.exists('.local_cache'):
	os.mkdir('.local_cache')

parser = argparse.ArgumentParser(
	prog = 'cfcl',
	description = 'Codeforces command line toolchain')
parser.add_argument('--pid')

contest_id = -1
try:
	contest_id = open('.local_cache/contest.cfg', 'r').read()
except:
	pass

parser.add_argument('--cid')
parser.add_argument('--test', 
	dest='test', 
	action='store_const', 
	const='True', 
	default='False')
parser.add_argument('-p', 
	dest='pid')
parser.add_argument('-c', 
	dest='cid')
parser.add_argument('-t', 
	dest='test',
	action='store_const', 
	const='True', 
	default='False')
parser.add_argument('tests_subset', 
	metavar='tests', type=int, nargs='*', default=[])

args = parser.parse_args()

tests_subset = args.tests_subset

run_tests = args.test
problem_id = args.pid

if args.cid:
	contest_id = args.cid
	if contest_id:
		open('.local_cache/contest.cfg', 'w').write(contest_id)

if not contest_id:
	print "Please provide contest id via --cid flag"
	exit()

if not problem_id:
	print "Please choose problem [A, B, C, D, E] to work with via --pid flag"
	exit()

if not problem_id in {'A', 'B', 'C', 'D', 'E'}:
	print "Provide correct problem id (A, B, C, D, E) provided: %s" % pid
	exit()

# Executing local run by default:
if run_tests == 'False':
	os.system('rm a.out; g++ -O2 -DSHTRIX %s.cpp; ./a.out' % problem_id)
	exit()

total_time_elapsed = time.time()

print "Running %s%s problem, expecting source filename %s.cpp" % (
	contest_id, problem_id, problem_id)

local_cache = '.local_cache/cached%sx%s' % (contest_id, problem_id)

if not os.path.exists(local_cache):
	cf_template = "/contest/%s/problem/%s"

	url = cf_template % (contest_id, problem_id)
	h = httplib.HTTPConnection('codeforces.com', timeout=1)

	cnt = 0
	while cnt < 10:
		try:
			h.request('GET', url)
			response = h.getresponse()
		except Exception as e:
			print e
			exit()
		if response.status != 200:
			print "Error occured while connecting by url: %s" % url
			cnt += 1
		else:
			break

	if cnt == 10:
		print "Unable to connect to codeforces."

	page = response.read()

	class SampleParser(HTMLParser):
		results = []
		current = []
		stack = []
		search_tag = ""
		read_now = False

		def __init__(self, _search_tag):
			self.results = []
			self.current = []
			self.stack = []
			self.read_now = False
			self.search_tag = _search_tag
			HTMLParser.__init__(self)

		def handle_starttag(self, tag, attrs):
			if self.read_now:
				self.stack.append(tag)

			for (x, y) in attrs:
				if x == 'class' and y == self.search_tag:
					self.read_now = True
					self.stack.append(tag)
		
		def handle_endtag(self, tag):
			if self.stack and self.stack[-1] == tag:
				self.stack.pop()
			if len(self.stack) == 0 and self.read_now:
				self.read_now = False
				self.results.append('\n'.join(self.current))	
				self.current = []

		def handle_data(self, data):
			if self.read_now:
				if self.stack and self.stack[-1] == 'pre':
					self.current.append(data)

		def feedx(self, str):
			self.feed(str)
			return self.results

	inputs = SampleParser('input').feedx(page)
	outputs = SampleParser('output').feedx(page)

	if len(inputs) != len(outputs):
		print "ooops... something went wrong while parsing input/output"
		print "check if problem input/output doesn't \
			   contain special characters e.g. '<'"
		exit()
	open(local_cache, 'w').write(str(len(inputs)))

	for i in xrange(0, len(inputs)):
		open('.local_cache/%sx%s%d.in' % (contest_id, problem_id, i), 'w').write(inputs[i])
		open('.local_cache/%sx%s%d.out' % (contest_id, problem_id, i), 'w').write(outputs[i].strip())

testcases_num = open(local_cache, 'r').read()
try:
	testcases_num = int(testcases_num)
except:
	print "wrong format for file %s" % local_cache
	exit()

testcases = []
for i in xrange(0, testcases_num):
	testcases.append(
		(i, 
		open('.local_cache/%sx%s%d.in' % (contest_id, problem_id, i)).read(), 
		open('.local_cache/%sx%s%d.out' % (contest_id, problem_id, i)).read() 
		)
	)	


compilation_line = 'rm a.out; g++ -O2 -DONLINE_JUDGE %s.cpp' % problem_id
ret = os.system(compilation_line)
if ret:
	exit()

def shift_tab(answer):
	return '\n'.join([('\t%s' % x) for x in answer.split('\n') if x])

for (id, input, output) in testcases:
	if not tests_subset or id in tests_subset:
		open('testcase.in', 'w').write(input)
		time_elapsed = time.time()
		os.system('./a.out < testcase.in > testcase.out')
		time_elapsed = time.time() - time_elapsed
		answer = open('testcase.out', 'r').read().strip()
		if answer == output:
			print "%s[%d] %sPASSED%s (in %.2lf seconds)" % (
				asciicolors.BOLDMAGENTA, id, asciicolors.GREEN, asciicolors.RESET, time_elapsed)
		else:
			print "%s[%d] %sFAILED%s" % (
				asciicolors.BOLDMAGENTA, id, asciicolors.RED, asciicolors.RESET)
			print shift_tab("Received:")
			print shift_tab(shift_tab(answer))
			print shift_tab("Expected:")
			print shift_tab(shift_tab(output))

total_time_elapsed = time.time() - total_time_elapsed
print "Finished executing script in %.3lf" % total_time_elapsed
