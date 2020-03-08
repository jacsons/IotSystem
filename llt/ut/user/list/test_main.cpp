#include <gtest/gtest.h>  

extern "C" {
#include "zmmalloc.h"
}

TEST(zmcalloc, zmcalloc_normal){  
	int *ptr;
	ptr = zmmalloc(sizeof(int), 0);

	EXPECT_EQ(sizeof(int), zmmalloc_size(ptr));
}  

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
