#include"ProceduralGeneration.h"

float pg::Noise(int x)
{
   
   x = (x << 13) ^ x;
   float k = (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
   return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float pg::SmoothedNoise(float x)
{
   return Noise(x) / 2.0 + Noise(x - 1) / 4.0 + Noise(x + 1) / 4.0;
}

float pg::QuanticCurve(float x)
{
   return x * x * x * (x * ( x * 6 - 15) + 10);
}

float pg::Interpolate(float a, float b, float x)
{
   float tmp = QuanticCurve(x);
   return tmp * (b - a) + a;
}

float pg::InterpolateNoise(float x)
{
   int integerX = int(x);
   float fractionalX = x - integerX;
   float v1 = SmoothedNoise(integerX);
   float v2 = SmoothedNoise(integerX + 1);
   return Interpolate(v1, v2, fractionalX);
}

float pg::PerlinNoise1D(float x,float persistence,int n)
{
   float total = 0;
   float frequency = 0;
   float amplitude = 0;
   for (int i = 0; i < n; i++)
   {
      amplitude = pow(persistence, i);
      frequency = pow(2, i);
      total += InterpolateNoise(x * frequency) * amplitude;
   }
   return total;
}
