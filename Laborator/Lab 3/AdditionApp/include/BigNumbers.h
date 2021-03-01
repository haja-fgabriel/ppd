#pragma once

#include <cassert>
#include <vector>
#include <string>

namespace BigNumbers
{
    void Add(
        std::vector<int>& Number1,
        std::vector<int>& Number2,
        std::vector<int>& Result,
        int InitialCarry,
        int* SendCarry = nullptr
    )
    {
        int carry = InitialCarry;
       
        if (Number1.size() < Number2.size())
            Number1.resize(Number2.size());
        else
            Number2.resize(Number1.size());

        Result.clear();
        Result.resize(Number1.size());
        for (size_t i = 0; i < Number1.size(); i++)
        {
            Result[i] = (Number1[i] + Number2[i] + carry) % 10;
            carry = (Number1[i] + Number2[i] + carry) / 10;
        }
        if (!SendCarry)
        {
            if (carry > 0)
                Result.push_back(carry);
        }
        else
        {
            *SendCarry = carry;
        }
    }
};