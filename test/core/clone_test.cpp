#include <gtest/gtest.h>

#include "core/clone.h"
#include "core/smart_ptr.h"

namespace {

using core::ICloneable;

class BaseClass : public ICloneable {
public:
  explicit BaseClass(int baseValue)
  : m_baseValue(baseValue)
  {}
  int getBaseValue() const
  {
    return m_baseValue;
  }
  CLONE_IMPL(BaseClass)

private:
  int m_baseValue;
};

class DerivedClass : public BaseClass {
public:
  explicit DerivedClass(int baseValue, int derivedValue)
  : BaseClass(baseValue),
    m_derivedValue(derivedValue)
  {}
  int getDerivedValue() const
  {
    return m_derivedValue;
  }
  CLONE_IMPL(DerivedClass)

private:
  int m_derivedValue;
};

}

/**
 * Test ICloneable behaviour within class hierarchies
 */
TEST(Clone, ClassHierarchies)
{
  using std::tr1::shared_ptr;

  BaseClass bc1(1012);
  shared_ptr<BaseClass> pbc2(bc1.clone());
  EXPECT_EQ(1012, pbc2->getBaseValue());

  DerivedClass dc1(1012, 2024);
  shared_ptr<DerivedClass> pdc2(dc1.clone());
  EXPECT_EQ(1012, pdc2->getBaseValue());
  EXPECT_EQ(2024, pdc2->getDerivedValue());
}
