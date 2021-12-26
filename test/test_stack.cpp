#include "../include/stack.h"
#include <gtest.h>

TEST(TStack, TStack_can_create_Test)
{
	ASSERT_NO_THROW(TStack<int> s);
} 

TEST(TStack, TStack_check_empty_Test)
{
	TStack<int> s;
    EXPECT_EQ(1, s.Empty());
} 

TEST(TStack, TStack_view_element_Test)
{
    TStack<int> s;
	s.Push(7);
	EXPECT_EQ(7, s.Top());
}

TEST(TStack, TStack_can_insert_element_into__Test)
{  
	TStack<int>s;
	s.Push(7);
	EXPECT_EQ(0, s.Empty());
}

TEST(TStack, TStack_can_put_element_larger_size_Test)
{
	TStack<int>s;
	for(int i=0;i< STACK_SIZE+2;i++)
	{s.Push(i);}
	ASSERT_NO_THROW(s.Top());
	EXPECT_EQ(STACK_SIZE+1, s.Top());
}

TEST(TStack, TStack_cant_take_element_from_empty_Test)
{
	TStack<int>s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, TStack_take_element_from_empty_Test)
{
	TStack<int>s;
	s.Push(7);
	EXPECT_EQ(7, s.Pop());
	EXPECT_EQ(1, s.Empty()); 
}

TEST(TStack, TStack_get_the_number_of_elements_Test)
{
	TStack<int>s;
	EXPECT_EQ(0, s.Count());
	for (int i = 0; i < 10; i++)
	{
		s.Push(i);
	}
	EXPECT_EQ(10, s.Count());
}

TEST(TStack, TStack_clean_Test)
{
	TStack<int>s;
	for (int i = 0; i < 10; i++)
	{
		s.Push(i);
	}
	s.Clear();
	EXPECT_EQ(1, s.Empty());
}