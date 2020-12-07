#include "pch.h"
#include "CppUnitTest.h"
#include "../DecisionTree/Header.h"
#include "../DecisionTree/DecisionTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace N;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(node_data_test_1)
		{
			node n;
			n.data = 2;
			Assert::IsTrue(n.data == 2);
		}

		TEST_METHOD(linked_list_constructor_1)
		{
			linked_list l = linked_list();
			Assert::IsTrue(l.header.data == -1);
		}
		TEST_METHOD(linked_list_add_1)
		{
			linked_list l = linked_list();
			l.add(5);
			Assert::IsTrue(l.header.data == 5);
		}
		TEST_METHOD(linked_list_add_2)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			Assert::IsTrue(l.header.next->data == 6);
		}
		TEST_METHOD(linked_list_add_3)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.add(7);
			Assert::IsTrue(l.header.next->next->data == 7);
		}
		TEST_METHOD(linked_list_remove_1)
		{
			linked_list l = linked_list();
			l.add(5);
			l.remove(5);
			Assert::IsTrue(l.header.data == -1);
		}
		TEST_METHOD(linked_list_remove_2)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.remove(5);
			Assert::IsTrue(l.header.data == 6);
		}
		TEST_METHOD(linked_list_remove_3)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.add(7);
			l.remove(6);
			Assert::IsTrue(l.header.next->data == 7);
		}
		TEST_METHOD(linked_list_remove_4)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.add(7);
			l.add(8);
			l.remove(7);
			Assert::IsTrue(l.header.next->next->data == 8);
		}
		TEST_METHOD(linked_list_remove_5)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.add(7);
			l.add(8);
			l.remove(8);
			Assert::IsTrue(l.header.next->next->next == nullptr);
		}
		TEST_METHOD(linked_list_remove_6)
		{
			linked_list l = linked_list();
			l.add(5);
			l.add(6);
			l.add(7);
			l.add(8);
			l.remove(9);
			Assert::IsTrue(l.header.next->next->next->data == 8);
		}
		
	};
}
