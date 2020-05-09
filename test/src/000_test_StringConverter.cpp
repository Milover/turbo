/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing StringConverter class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <functional>
#include <mutex>
#include <thread>
#include <utility>

#include "StringConverter.h"
#include "General.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void pad(String& s)
{
	// leading pad
	if (test::randomBool())
	{
		s = test::randomString
		(
			static_cast<size_t>(test::randomInt(1, 20)),
			R"(	 
			)"
		)
		  + s;
	}

	// trailing pad
	if (test::randomBool())
	{
		s += test::randomString
		(
			static_cast<size_t>(test::randomInt(1, 20)),
			R"(	 
			)"
		);
	}
}

void good(String& s)
{
	s = std::to_string
	(
		test::randomInt(-10000, 10000)
	);
	pad(s);
}


void garbage(String& s)
{
	s = test::randomString
	(
		static_cast<size_t>(test::randomInt(1, 20)),
		R"(0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 	
		)"
	);

	// so we don't accidentally create a good one
	s += "x";
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

std::mutex m_testPass;
void testFunction(bool& testPass, int numIter)
{
	assert(numIter >= 0);

	// converters
	StringConverter<Integer>	iSC {};
	StringConverter<Float>		fSC {};
	StringConverter<Vector>		vSC {};

	// to convert from
	String iStr, fStr, vStr;

	// to convert to
	[[maybe_unused]] Integer i;
	[[maybe_unused]] Float f;
	[[maybe_unused]] Vector v;

	// ammount we should catch
	int iCount {0};
	int fCount {0};
	int vCount {0};
	// ammount we caught
	int iCaught {0};
	int fCaught {0};
	int vCaught {0};

	for (int iter {0}; iter < numIter; ++iter)
	{
		// generate a good value
		if
		(
			bool(test::randomInt(0, 1))
		)
		{
			good(iStr);
			fStr = iStr;
			// make sure we have 3 values
			vStr = iStr + " " + iStr + " " + iStr;
		}
		else
		{
			garbage(iStr);
			garbage(fStr);
			garbage(vStr);

			++iCount;
			++fCount;
			++vCount;
		}

		// integers
		try { i = iSC(iStr); }
		catch(...) { ++iCaught; }
		// integers
		try { f = fSC(fStr); }
		catch(...) { ++fCaught; }
		// vectors
		try { v = vSC(vStr); }
		catch(...) { ++vCaught; }
	}

	std::lock_guard<std::mutex> guard(m_testPass);
	testPass = iCaught == iCount
			&& fCaught == fCount
			&& vCaught == vCount;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// we assume hyperthreading/smt, which we don't want
	auto numThreads {std::thread::hardware_concurrency() / 2};
	if (numThreads == 0)
		numThreads = 2;		// guesstimate

	bool testPass {true};
	decltype(numThreads) numIter {1000};	// how ever many we like

	if (output)
		test::echo("Running on ", numThreads, " threads.");

	// do work
	std::vector<std::thread> threads(numThreads);

	for (decltype(numThreads) i {0}; i < numThreads; ++i)
		threads[i] = std::thread
		(
			testFunction,
			std::ref(testPass),
			numIter
		);

	for (auto& t : threads)
		t.join();

	if (output)
		test::echo("Ran ", numThreads * numIter, " tests in total.");

	// we should've caught everything
	test::compareTest
	(
		pass,
		testPass,
		output,
		"Checking caught exceptions"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
