#include <vector>
#include <chrono>

#pragma once

namespace weekTwo
{

  class BitArray
  {
  public:
    std::vector<uint64_t> bits;

    BitArray(size_t n)
    {
      bits.resize((n + 63) / 64);
    }

    bool get(size_t pos) const
    {
      if (pos >= bits.size() * 64)
      {
        throw std::out_of_range("Bit position out of range.");
      }
      bool res = (bits[pos / 64] >> (pos % 64)) & 1;

      return res;
    }

    void set(size_t pos, bool value)
    {
      if (pos >= bits.size() * 64)
      {
        throw std::out_of_range("Bit position out of range.");
      }
      if (value)
      {
        bits[pos / 64] |= 1ULL << (pos % 64);
      }
      else
      {
        bits[pos / 64] &= ~(1ULL << (pos % 64));
      }
    }

    size_t sum(size_t pos) const
    {
      size_t count = 0;

      for (size_t i = 0; i <= pos / 64; i++)
      {
        if (i < pos / 64)
        {
          count += __builtin_popcountll(bits[i]);
        }
        else
        {
          uint64_t mask = (1ULL << (pos % 64)) - 1;
          count += __builtin_popcountll(bits[i] & mask);
        }
      }

      return count;
    }

    size_t location(size_t i) const
    {
      size_t left = 0;
      size_t right = bits.size() * 64 - 1;

      while (left < right)
      {
        size_t mid = left + (right - left) / 2;

        if (sum(mid) < i)
        {
          left = mid + 1;
        }
        else
        {
          right = mid;
        }
      }


      return left ;
    }
  };
}