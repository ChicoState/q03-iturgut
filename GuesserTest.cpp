/**
 * Unit Tests for the Guesser class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Test constructor with normal length string
TEST(GuesserTest, constructor_normal_string)
{
  Guesser guesser("Secret");
  ASSERT_EQ(guesser.remaining(), 3);
}

// Test constructor with string longer than 32 characters
TEST(GuesserTest, constructor_long_string)
{
  std::string longSecret = "ThisIsAVeryLongSecretThatShouldBeTruncatedAtThirtyTwoCharacters";
  Guesser guesser(longSecret);
  ASSERT_EQ(guesser.remaining(), 3);
  
  ASSERT_FALSE(guesser.match("WrongSecret"));
}

// Test correct match
TEST(GuesserTest, correct_match)
{
  Guesser guesser("Secret");
  ASSERT_TRUE(guesser.match("Secret"));
  ASSERT_EQ(guesser.remaining(), 3);
}

// Test incorrect match with small distance
TEST(GuesserTest, incorrect_match_small_distance)
{
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("Secrat")); // Distance = 1
  ASSERT_EQ(guesser.remaining(), 2);
}

// Test incorrect match with distance = 2
TEST(GuesserTest, incorrect_match_distance_two)
{
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("Sacrat")); // Distance = 2
  ASSERT_EQ(guesser.remaining(), 2);
}

// Test incorrect match with large distance (should lock)
TEST(GuesserTest, incorrect_match_large_distance)
{
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("Password")); // Distance > 2
  ASSERT_EQ(guesser.remaining(), 3); // Remaining should not decrease
  
  ASSERT_FALSE(guesser.match("Secret")); // Even correct match should fail
}

// Test running out of guesses
TEST(GuesserTest, run_out_of_guesses)
{
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("Secrat")); // Distance = 1
  ASSERT_EQ(guesser.remaining(), 2);
  
  ASSERT_FALSE(guesser.match("Secrat")); // Distance = 1
  ASSERT_EQ(guesser.remaining(), 1);
  
  ASSERT_FALSE(guesser.match("Secrat")); // Distance = 1
  ASSERT_EQ(guesser.remaining(), 0);
  
  ASSERT_FALSE(guesser.match("Secret")); // Even correct match should fail
}

// Test reset of guesses after correct match
TEST(GuesserTest, reset_after_correct_match)
{
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("Secrat")); // Distance = 1
  ASSERT_EQ(guesser.remaining(), 2);
  
  ASSERT_TRUE(guesser.match("Secret")); // Correct match
  ASSERT_EQ(guesser.remaining(), 2);
}

// Test different string lengths
TEST(GuesserTest, different_string_lengths)
{
  Guesser guesser("Secret");
  
  ASSERT_FALSE(guesser.match("Secr")); // Distance = 2
  ASSERT_EQ(guesser.remaining(), 2);
  
  ASSERT_FALSE(guesser.match("Secretive")); 
  ASSERT_EQ(guesser.remaining(), 2);
  
  ASSERT_FALSE(guesser.match("SecretVeryLongGuess")); 
  ASSERT_EQ(guesser.remaining(), 2);
  
  ASSERT_FALSE(guesser.match("Secret")); // Even correct match should fail
}

// Test empty strings
TEST(GuesserTest, empty_strings)
{
  Guesser emptyGuesser("");
  ASSERT_TRUE(emptyGuesser.match(""));
  ASSERT_FALSE(emptyGuesser.match("something"));
  
  Guesser guesser("Secret");
  ASSERT_FALSE(guesser.match("")); // Distance = 6
  ASSERT_FALSE(guesser.match("Secret")); // Even correct match should fail
}
