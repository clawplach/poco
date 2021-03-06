//
// Tuple.cpp
//
// $Id: //poco/Main/Data/samples/Tuple/src/Tuple.cpp#1 $
//
// This sample demonstrates the Data library.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


#include "Poco/SharedPtr.h"
#include "Poco/Tuple.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include <vector>
#include <iostream>


using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;


int main(int argc, char** argv)
{
	typedef Poco::Tuple<std::string, std::string, int> Person;
	typedef std::vector<Person> People;

	// create a session
	Session session("SQLite", "sample.db");

	// drop sample table, if it exists
	session << "DROP TABLE IF EXISTS Person", now;
	
	// (re)create table
	session << "CREATE TABLE Person (Name VARCHAR(30), Address VARCHAR, Age INTEGER(3))", now;
	
	// insert some rows
	People people;
	people.push_back(Person("Bart Simpson",	"Springfield", 12));
	people.push_back(Person("Lisa Simpson",	"Springfield", 10));
	
	Statement insert(session);
	insert << "INSERT INTO Person VALUES(:name, :address, :age)",
		use(people), now;
	
	people.clear();

	// a simple query
	Statement select(session);
	select << "SELECT Name, Address, Age FROM Person",
		into(people),
		now;
	
	for (People::const_iterator it = people.begin(); it != people.end(); ++it)
	{
		std::cout << "Name: " << it->get<0>() << 
			", Address: " << it->get<1>() << 
			", Age: " << it->get<2>() <<std::endl;
	}

	return 0;
}
