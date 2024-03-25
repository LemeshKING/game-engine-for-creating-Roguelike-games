#include"ProceduralGeneration.h"

float pg::Noise(unsigned int x)
{
   std::bitset<32> bitset1{ x };
   bitset1 = (bitset1 << 13) ^ bitset1;
   x = bitset1.to_ulong();
   return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float pg::SmoothedNoise(float x)
{
   unsigned int _x = (unsigned int)x;
   return Noise(_x) / 2 + Noise(x-1)/4 + Noise(x + 1) / 4;
}

float pg::QuanticCurve(float x)
{
   return x*x*x*(x*(x*6-15)+10);
}

float pg::Interpolate(float a, float b, float x)
{
   float tmp = QuanticCurve(x);
   return tmp*(b-a)+a;
}

float pg::InterpolateNoise(float x)
{
   int integerX = int(x);
   float fractionalX = x - integerX;
   float v1 = SmoothedNoise(integerX);
   float v2 = SmoothedNoise(integerX + 1);
   return Interpolate(v1,v2,fractionalX);
}

float pg::PerlinNoise1D(float x,float persistence,int n)
{
   float total = 0;
   float frequency = 0;
   float amplitude = 0;
   for (int i = 0; i < n; i++)
   {
      amplitude = pow(persistence,i);
      frequency = pow(2,i);
      total += InterpolateNoise(x*frequency)*amplitude;
   }
   return total;
}
