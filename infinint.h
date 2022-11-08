#include <vector>
#include <string>
#include <iostream>

class infinint
{
private:
    bool neg;
    std::vector<bool> n;

public:
    infinint()
    {
        neg = 0;
        n.reserve(64);
    }
    infinint(long long num)
    {
        setNeg(0);
        if (num < 0)
        {
            setNeg(1);
            num = 0-num;
        }
        n.reserve(64);
        while (num > 0)
        {
            n.push_back(num % 2);
            num /= 2;
        }
        //std::cout << std::to_string(toLong()) << "\n";
    }
    infinint(std::vector<bool> num)
    {
        setNeg(0);
        setVector(num);
    }
    std::vector<bool> getVector() const
    {
        return n;
    }
    void setVector(std::vector<bool> nw)
    {
        n = {};
        n.reserve(64);
        for (int i = 0; i < nw.size(); i++)
        {
            n.push_back(nw[i]);
        }
    }
    bool getNeg() const
    {
        return neg;
    }
    void setNeg(bool nw)
    {
        neg = nw;
    }
    void debug() const
    {
        for (int i : n)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    long long toLong() const
    {
        long long num = 0;
        for (int i = n.size() - 1; i >= 0; i--)
        {
            num *= 2;
            num += n[i];
        }
        if(getNeg()){
            num = -num;
        }
        return num;
    }
    std::string toString() const{
        //TODO (vital component)
        return std::to_string(toLong());
    }
    operator long long()
    {
        return toLong();
    }
    long long size() const
    {
        return n.size();
    }
    friend infinint abs(infinint i)
    {
        i.setNeg(0);
        return i;
    }

    infinint &operator=(infinint rhs)
    {
        n = rhs.n;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const infinint &obj)
    {
        os << obj.toString();
        return os;
    }
    friend std::istream &operator>>(std::istream &is, infinint &obj)
    {
        long long num;
        is >> num;
        obj = *new infinint(num);
        obj.setNeg(num < 0);
        return is;
    }
    friend inline bool operator==(const infinint &lhs, const infinint &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        if(lhs.getNeg() != rhs.getNeg()){
            return false;
        }
        auto v1 = lhs.getVector(), v2 = rhs.getVector();
        for (int i = 0; i < v1.size(); i++)
        {
            if (v1[i] != v2[i])
            {
                return false;
            }
        }
        return true;
    }
    friend inline bool operator!=(const infinint &lhs, const infinint &rhs) { return !operator==(lhs, rhs); }
    friend inline bool operator<(const infinint &lhs, const infinint &rhs)
    {
        if((lhs-rhs).getNeg()){
            return true;
        }
        return false;
    }
    friend inline bool operator>(const infinint &lhs, const infinint &rhs) { return operator<(rhs, lhs); }
    friend inline bool operator<=(const infinint &lhs, const infinint &rhs) { return !operator>(lhs, rhs); }
    friend inline bool operator>=(const infinint &lhs, const infinint &rhs) { return !operator<(lhs, rhs); }

    infinint &operator++()
    {
        (*this) += 1;
        return *this;
    }
    infinint operator++(int)
    {
        infinint tmp(*this);
        operator++();
        return tmp;
    }

    infinint &operator+=(const infinint &rhs)
    {
        auto v1 = getVector(), v2 = rhs.getVector();
        if (v1.size() < v2.size())
        {
            std::swap(v1, v2);
        }
        int carry = 0;
        for (int i = 0; i < v2.size(); i++)
        {
            int sum = v1[i] + v2[i] + carry;
            carry = sum / 2;
            v1[i] = sum % 2;
        }
        for (int i = v2.size(); i < v1.size(); i++)
        {
            int sum = v1[i] + carry;
            carry = sum / 2;
            v1[i] = sum % 2;
        }
        if (carry != 0)
        {
            v1.push_back(1);
        }
        setVector(v1);
        return *this;
    }
    friend inline infinint operator+(infinint lhs, const infinint &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    infinint &operator--()
    {
        (*this) -= 1;
        return *this;
    }
    infinint operator--(int)
    {
        infinint tmp(*this);
        operator--();
        return tmp;
    }

    infinint &operator-=(const infinint &rhs)
    {
        if(getNeg() == 0 && rhs.getNeg() == 1){
            return (*this) += infinint(rhs.getVector());
        }
        if(getNeg() == 1 && rhs.getNeg() == 0){
            setNeg(0);
            (*this) += infinint(rhs.getVector());
            setNeg(1);
            return *this;
        }
        bool negative = false;
        if(getNeg() == 1 && rhs.getNeg() == 1){
            setNeg(0);
            (*this) = infinint(rhs.getVector()) - (*this);
            return *this;
        }
        auto v1 = getVector(), v2 = rhs.getVector();
        if (v1.size() < v2.size())
        {
            negative = !negative;
            std::swap(v1, v2);
            //throw std::invalid_argument("Negative infinints not yet supported");
        }
        int borrow = 0;
        for (int i = 0; i < v2.size(); i++)
        {
            int sum = v1[i] - v2[i] - borrow;
            if (sum < 0)
            {
                borrow = 1;
                sum += 2;
            }
            else
            {
                borrow = 0;
            }
            v1[i] = sum;
        }
        for (int i = v2.size(); i < v1.size(); i++)
        {
            int sum = v1[i] - borrow;
            if (sum < 0)
            {
                borrow = 1;
                sum += 2;
            }
            else
            {
                borrow = 0;
            }
            v1[i] = sum;
        }
        int s = v1.size();
        while(v1.back() == 0){
            v1.pop_back();
        }
        setVector(v1);
        if (borrow != 0)
        {
            std::vector<bool> v3(s + 1);
            v3[v1.size()] = 1;
            (*this) = infinint(v3) - (*this);
            (*this).setNeg(1);
        }
        if(negative){
            (*this).setNeg(!(*this).getNeg());
        }
        return *this;
    }
    friend inline infinint operator-(infinint lhs, const infinint &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};
