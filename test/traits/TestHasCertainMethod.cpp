#include <gtest/gtest.h>

#include <Traits.hpp>

class Handler
{
public:
  void handle() {}
};

class UsesHandle : public stdlike::HasHandle<Handler> {

};

// HasMethod(clone, T*);

TEST(TestHasCertainMethod, compilesFineWhenMethodIsPresent) {
   UsesHandle uh; 
}
