#include "gtest/gtest.h"
#include "../src/operations.h"
#include <array>
#include <string>
#include <fstream>
#include <stdexcept>
 
using namespace std;

template <int N>
class Vect{
public:
    Vect(double c = 0.0){ mdata.fill(c); }

    Vect(Vect const &) = delete;
    Vect(Vect &&) = delete;
    Vect & operator=(Vect const &) = delete;
    Vect & operator=(Vect &&) = delete;

    void fill(double c){ mdata.fill(c); }

    double  operator[](std::size_t i) const { return mdata[i];}
    double& operator[](std::size_t i) { return mdata[i];}
private:
    std::array<double,N> mdata;

};

TEST(ET, Basic) {
   Vector<4, Vect<4>> x,y(1.0),z;
   x[0] = 0; x[1] = 1; x[2] = 2; x[3] = 3;
   z = x+ y;
   ASSERT_EQ(z[0],1);
   ASSERT_EQ(z[1],2);
   ASSERT_EQ(z[2],3);
   ASSERT_EQ(z[3],4);
   z = x - y;
   ASSERT_EQ(z[0],-1);
   ASSERT_EQ(z[1],0);
   ASSERT_EQ(z[2],1);
   ASSERT_EQ(z[3],2);

   z = 2*z;
   ASSERT_EQ(z[0],-2);
   ASSERT_EQ(z[1],0);
   ASSERT_EQ(z[2],2);
   ASSERT_EQ(z[3],4);

   double w = 2.0;
   z = z*w;
   ASSERT_EQ(z[0],-4);
   ASSERT_EQ(z[1],0);
   ASSERT_EQ(z[2],4);
   ASSERT_EQ(z[3],8);
  }

TEST(ET, Level1) {
   Vector<4, Vect<4>> x,y(1.0),z;
   x[0] = 0; x[1] = 1; x[2] = 2; x[3] = 3;
   z = 2*x+ y*2;
   ASSERT_EQ(z[0],2);
   ASSERT_EQ(z[1],4);
   ASSERT_EQ(z[2],6);
   ASSERT_EQ(z[3],8);
   z = (2*x + y*2) - z;
   ASSERT_EQ(z[0],0);
   ASSERT_EQ(z[1],0);
   ASSERT_EQ(z[2],0);
   ASSERT_EQ(z[3],0);

   z = 4.0*(x*2.0 + y);
   for(std::size_t i=0; i<4; ++i)
       ASSERT_EQ(z[i], 8*x[i]+4*y[i]);
   z = 1.0 + (1.2*x + y*2.0)*4.0 - x + 2.0;
   for(std::size_t i=0; i<4; ++i)
       ASSERT_EQ(z[i], 3+4*(1.2*x[i]+2*y[i]) -x[i]);
  }

TEST(ET, Level2) {
    Vector<4, Vect<4>> x,y(1.0),z;
    x[0] = 0; x[1] = 1; x[2] = 2; x[3] = 3;
    Matrix<4,4> M;
    M(0,0)=M(1,1)=M(2,2)=1;
    M(3,3)=3;
    M(1,0)=M(2,1)=M(3,2)=0;
    M(3,0)=2;
    M(0,1)=0;
    M(0,2)=M(0,3)=1;
    M(1,2)=2;
    M(1,3)=0;
    M(2,3)=3;
    M(2,0) = 1;
    M(3,1)=0;
    z=M*x;
    ASSERT_FLOAT_EQ(z[0],5);
    ASSERT_FLOAT_EQ(z[1],5);
    ASSERT_FLOAT_EQ(z[2],11);
    ASSERT_FLOAT_EQ(z[3],9);

    z = M*x +y;
    ASSERT_FLOAT_EQ(z[0],6);
    ASSERT_FLOAT_EQ(z[1],6);
    ASSERT_FLOAT_EQ(z[2],12);
    ASSERT_FLOAT_EQ(z[3],10);

    z = M*(x*3.0 + y);
    ASSERT_FLOAT_EQ(z[0],18);
    ASSERT_FLOAT_EQ(z[1],18);
    ASSERT_FLOAT_EQ(z[2],38);
    ASSERT_FLOAT_EQ(z[3],32);

    z = y + M*x;
    ASSERT_FLOAT_EQ(z[0],6);
    ASSERT_FLOAT_EQ(z[1],6);
    ASSERT_FLOAT_EQ(z[2],12);
    ASSERT_FLOAT_EQ(z[3],10);

    z = 2*(M*x);
    ASSERT_FLOAT_EQ(z[0],10);
    ASSERT_FLOAT_EQ(z[1],10);
    ASSERT_FLOAT_EQ(z[2],22);
    ASSERT_FLOAT_EQ(z[3],18);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
