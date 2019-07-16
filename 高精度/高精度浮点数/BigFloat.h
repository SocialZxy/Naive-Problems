#ifndef _BIGFLOAT_H_
#define _BIGFLOAT_H_

#include "BigFloatReference.h"

void DividedByZeroException::error() {
    cout<<"Divided By Zero Exception!"<<endl;
}

BigFloat operator-(const BigFloat& op) {
    BigFloat temp(op);
    temp.tag = !temp.tag;
    return temp;
}
void BigFloat::trim() {
    vector<char>::reverse_iterator iter = integer.rbegin();
    while(!integer.empty() && (*iter) == 0) {
        integer.pop_back();
        iter=integer.rbegin();
    }
    if( integer.size()==0 ) {
        tag = true;
        integer.push_back(0);
    }
    vector<char>::iterator it = decimal.begin();
    while(!decimal.empty() && (*it) == 0) {
        it = decimal.erase(it);
    }
    if( decimal.size()==0 ) {
        tag = true;
        decimal.push_back(0);
    }
}

const BigFloat BigFloat::ZERO=BigFloat(0);
const BigFloat BigFloat::ONE =BigFloat(1);
const BigFloat BigFloat::TEN =BigFloat(10);

BigFloat::BigFloat(int val) {
    if (val >= 0)
        tag = true;
    else {
        tag = false;
        val *= (-1);
    }
    do {
        integer.push_back( (char)(val%10) );
        val /= 10;
    } while ( val != 0 );
    decimal.push_back(0);
}

BigFloat::BigFloat( ) {
    tag = true;
    integer.push_back(0);
    decimal.push_back(0);
}


BigFloat::BigFloat(string& def) {
    bool type = true;
    for(string::reverse_iterator iter = def.rbegin() ; iter < def.rend();  iter++) {
        char ch = (*iter);
        if(ch == '.') {
            type = false;
            iter++;
        }
        if (iter == def.rend()-1) {
            if ( ch == '+' )
                break;
            if(ch == '-' ) {
                tag = false;
                break;
            }
        }

        if(type)
            decimal.push_back( (char)((*iter) - '0' ) );
        else
            integer.push_back( (char)((*iter) - '0' ) );
    }
}

BigFloat::BigFloat(const BigFloat &op) {
    integer = op.integer;
    decimal = op.decimal;
    tag = op.tag;
}

BigFloat BigFloat::operator=(const BigFloat& op) {
    integer = op.integer;
    decimal = op.decimal;
    tag = op.tag;
    return (*this);
}

BigFloat BigFloat::abs() const  {
    if(tag)
        return (*this);
    else
        return -(*this);
}

BigFloat BigFloat::pow(int a) {
    BigFloat res(1);
    for(int i=0; i<a; i++)
        res*=(*this);
    return res;
}

ostream& operator<<(ostream& stream,const BigFloat& val) {
    if (!val.tag)
        stream << "-";
    for ( vector<char>::const_reverse_iterator iter = val.integer.rbegin(); iter != val.integer.rend() ; iter++)
        stream << (char)((*iter) + '0');
    cout<<'.';
    for ( vector<char>::const_reverse_iterator iter = val.decimal.rbegin(); iter != val.decimal.rend() ; iter++)
        stream << (char)((*iter) + '0');
    return stream;
}

istream& operator>>(istream& stream, BigFloat& val) {
    string str;
    stream >> str;
    val=BigFloat(str);
    return stream;
}

BigFloat operator+=(BigFloat& op1,const BigFloat& op2) {
    if( op1.tag == op2.tag ) {
        vector<char>::iterator iter1;
        vector<char>::const_iterator iter2,it;

        int a = op1.decimal.size();
        int b = op2.decimal.size();
        char to_add = 0;
        if(a<b) {
            iter1 = op1.decimal.begin();
            iter2 = op2.decimal.begin();
            iter2 = iter2 - (a-b);

            while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()) {
                (*iter1) = (*iter1) + (*iter2) + to_add;
                to_add = ((*iter1) > 9);
                (*iter1) = (*iter1) % 10;
                iter1++;
                iter2++;
            }
            it = op2.decimal.begin();
            iter2 = op2.decimal.end();
            iter2 = iter2 - a -1;
            while(iter2 != it) {
                op1.decimal.insert(op1.decimal.begin(),*iter2);
                iter2--;
            }
            op1.decimal.insert(op1.decimal.begin(),*iter2);
            iter1 = op1.decimal.begin();
        } else if(a>b) {
            iter1 = op1.decimal.begin();
            iter1 = iter1+(a-b);
            iter2 = op2.decimal.begin();
            while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()) {
                (*iter1) = (*iter1) + (*iter2) + to_add;
                to_add = ((*iter1) > 9);
                (*iter1) = (*iter1) % 10;
                iter1++;
                iter2++;
            }
        } else {
            iter1 = op1.decimal.begin();
            iter2 = op2.decimal.begin();
            while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()) {
                (*iter1) = (*iter1) + (*iter2) + to_add;
                to_add = ((*iter1) > 9);
                (*iter1) = (*iter1) % 10;
                iter1++;
                iter2++;
            }
        }


        iter1 = op1.integer.begin();
        iter2 = op2.integer.begin();

        while ( iter1 != op1.integer.end() && iter2 != op2.integer.end()) {
            (*iter1) = (*iter1) + (*iter2) + to_add;
            to_add = ((*iter1) > 9);
            (*iter1) = (*iter1) % 10;
            iter1++;
            iter2++;
        }
        while ( iter1 != op1.integer.end() ) {
            (*iter1) = (*iter1) + to_add;
            to_add = ( (*iter1) > 9 );
            (*iter1) %= 10;
            iter1++;
        }
        while ( iter2 != op2.integer.end() ) {
            char val = (*iter2) + to_add;
            to_add = (val > 9) ;
            val %= 10;
            op1.integer.push_back(val);
            iter2++;
        }
        if( to_add != 0 )
            op1.integer.push_back(to_add);
        return op1;
    } else {
        if (op1.tag)
            return op1 -= (-op2);
        else
            return op1= op2 - (-op1);
    }
}

BigFloat operator-=(BigFloat& op1,const BigFloat& op2) {
    if( op1.tag == op2.tag ) {
        if(op1.tag)  {
            if(op1 < op2) {
                BigFloat op(op2 - op1);
                op1 = -op;
                return op1;
            }
        } else {
            if(-op1 > -op2)
                return op1=-((-op1)-(-op2));
            else
                return op1= (-op2) - (-op1);
        }

        char to_substract = 0;
        int a = op1.decimal.size();
        int b = op2.decimal.size();
        vector<char>::iterator it1 = op1.decimal.begin();
        vector<char>::const_iterator it2 = op2.decimal.begin();
        if(a>b) {
            a -= b;
            it1 = it1 + a;
        } else {
            int number = b-a;
            while(number!=0) {
                op1.decimal.insert(op1.decimal.begin(),'0');
                number--;
            }
        }
        while ( it1 != op1.decimal.end() && it2 != op2.decimal.end()) {
            (*it1) = (*it1) - (*it2) - to_substract;
            to_substract = 0;
            if( (*it1) < 0 ) {
                to_substract=1;
                (*it1) += 10;
            }
            it1++;
            it2++;
        }
        vector<char>::iterator iter1;
        vector<char>::const_iterator iter2;
        iter1 = op1.integer.begin();
        iter2 = op2.integer.begin();

        while ( iter1 != op1.integer.end() && iter2 != op2.integer.end()) {
            (*iter1) = (*iter1) - (*iter2) - to_substract;
            to_substract = 0;
            if( (*iter1) < 0 ) {
                to_substract=1;
                (*iter1) += 10;
            }
            iter1++;
            iter2++;
        }
        while ( iter1 != op1.integer.end() ) {
            (*iter1) = (*iter1) - to_substract;
            to_substract = 0;
            if( (*iter1) < 0 ) {
                to_substract=1;
                (*iter1) += 10;
            } else
                break;
            iter1++;
        }
        op1.trim();
        return op1;
    } else {
        if (op1 > BigFloat::ZERO)
            return op1 += (-op2);
        else
            return op1 = -(op2 + (-op1));
    }
}
BigFloat operator*=(BigFloat& op1,const BigFloat& op2) {
    BigFloat result(0);
    if (op1 == BigFloat::ZERO || op2==BigFloat::ZERO)
        result = BigFloat::ZERO;
    else {
        int size = 0;
        vector<char> op_temp1(op1.integer.begin(), op1.integer.end());
        if(op1.decimal.size()!=1||(op1.decimal.size()==1&&(*op1.decimal.begin())!=0)) {
            op_temp1.insert(op_temp1.begin(),op1.decimal.begin(), op1.decimal.end());
            size += op1.decimal.size();
        }
        vector<char> op_temp2(op2.integer.begin(), op2.integer.end());
        if(op2.decimal.size()!=1||(op2.decimal.size()==1&&(*op2.decimal.begin())!=0)) {
            op_temp2.insert(op_temp2.begin(),op2.decimal.begin(), op2.decimal.end());
            size += op2.decimal.size();
        }
        vector<char>::const_iterator iter2 = op_temp2.begin();
        while( iter2 != op_temp2.end() ) {
            if(*iter2 != 0) {
                deque<char> temp(op_temp1.begin(), op_temp1.end());
                char to_add = 0;
                deque<char>::iterator iter1 = temp.begin();
                while( iter1 != temp.end() ) {
                    (*iter1) *= (*iter2);
                    (*iter1) += to_add;
                    to_add = (*iter1) / 10;
                    (*iter1) %= 10;
                    iter1++;
                }
                if( to_add != 0)
                    temp.push_back( to_add );
                int num_of_zeros = iter2 - op_temp2.begin();
                while(  num_of_zeros--)
                    temp.push_front(0);
                BigFloat temp2;
                temp2.integer.clear();
                temp2.integer.insert( temp2.integer.end(), temp.begin(), temp.end() );
                temp2.trim();
                result = result + temp2;

            }
            iter2++;
        }
        result.tag = ( (op1.tag && op2.tag) || (!op1.tag && !op2.tag) );
        if(size!=0) {
            result.decimal.clear();
            result.decimal.insert(result.decimal.begin(), result.integer.begin(), result.integer.begin()+size);
            result.integer.erase(result.integer.begin(), result.integer.begin()+size);
        }
    }
    op1 = result;
    return op1;
}
BigFloat operator/=(BigFloat& op1,const BigFloat& op2) throw(DividedByZeroException) {
    if(op2 == BigFloat::ZERO)
        throw DividedByZeroException();
    if(op1 == BigFloat::ZERO)
        return op1;
    BigFloat op_temp2 = op2;
    BigFloat op_temp1 = op1;
    int Integer_Size = 0;
    if((op_temp2.decimal.size() == 1)&&(*(op_temp2.decimal.begin()) == 0)) {    }
    else {

        int t = op_temp2.decimal.size();
        while(t--) {
            op_temp1 = op_temp1*BigFloat::TEN;
            op_temp2 = op_temp2*BigFloat::TEN;
        }
    }
    if(op_temp1<op_temp2) {
        while(op_temp1>op_temp2) {
            op_temp1 *= BigFloat::TEN;
            Integer_Size--;
        }
    } else {
        while(op_temp1>op_temp2) {
            op_temp1.decimal.push_back(*op_temp1.integer.begin());
            op_temp1.integer.erase(op_temp1.integer.begin());
            Integer_Size++;
        }
    }
    int k = ACCURACY;
    BigFloat re(0);
    while(k--) {
        if(op_temp1<op_temp2) {
            op_temp1 = op_temp1*BigFloat::TEN;
            re = re*BigFloat::TEN;
        } else {
            int i;
            BigFloat compare;
            for(i=2; i<10; i++) {
                BigFloat BF(i);
                compare = op_temp2*BF;
                if(compare>op_temp1)
                    break;
            }
            compare -= op_temp2;
            op_temp1 -= compare;
            BigFloat index(i-1);
            re = re + index;
        }
    }
    if(re.integer.size()>Integer_Size) {
        vector<char> temp(re.integer.begin(), re.integer.end());
        re.integer.assign(temp.end() - Integer_Size, temp.end());
        re.decimal.insert(re.decimal.begin(), temp.begin(),temp.end() - Integer_Size);
    } else {
        int t = Integer_Size - re.integer.size();
        while(t--) {
            re = re*BigFloat::TEN;
        }
    }

    op1 = re;
    op1.trim();
    op1.tag = ( (op1.tag && op2.tag) || (!op1.tag && !op2.tag) );
    return op1;
}
BigFloat operator+(const BigFloat& op1,const BigFloat& op2) {
    BigFloat temp(op1);
    temp += op2;
    return temp;
}
BigFloat operator-(const BigFloat& op1,const BigFloat& op2) {
    BigFloat temp(op1);
    temp -= op2;
    return temp;
}
BigFloat operator*(const BigFloat& op1,const BigFloat& op2) {
    BigFloat temp(op1);
    temp *= op2;
    return temp;
}
BigFloat operator/(const BigFloat& op1,const BigFloat& op2) throw(DividedByZeroException) {
    BigFloat temp(op1);
    temp /= op2;
    return temp;
}
bool operator<(const BigFloat& op1,const BigFloat& op2) {
    bool sign;
    if( op1.tag != op2.tag ) {
        sign =  !op1.tag;
        return sign;
    } else {
        if(op1.integer.size() != op2.integer.size()) {
            if(op1.tag) {
                sign = op1.integer.size()<op2.integer.size();
                return sign;
            } else {
                sign = op1.integer.size()>op2.integer.size();
                return sign;
            }
        }
        vector<char>::const_reverse_iterator iter1,iter2;
        iter1 = op1.integer.rbegin();
        iter2 = op2.integer.rbegin();
        while( iter1 != op1.integer.rend() ) {
            if(  op1.tag &&  *iter1 < *iter2 )
                return true;
            if(  op1.tag &&  *iter1 > *iter2 )
                return false;
            if( !op1.tag &&  *iter1 > *iter2 )
                return true;
            if( !op1.tag &&  *iter1 < *iter2 )
                return false;
            iter1++;
            iter2++;
        }
        vector<char>::const_reverse_iterator it1,it2;
        it1 = op1.decimal.rbegin();
        it2 = op2.decimal.rbegin();
        while( it1 != op1.decimal.rend() && it2 != op2.decimal.rend()) {
            if(  op1.tag &&  *it1 < *it2 )
                return true;
            if(  op1.tag &&  *it1 > *it2 )
                return false;
            if( !op1.tag &&  *it1 > *it2 )
                return true;
            if( !op1.tag &&  *it1 < *it2 )
                return false;
            it1++;
            it2++;
        }
        return (op1.tag && it2!=op2.decimal.rend())
               || (!op1.tag && it1!=op1.decimal.rend());
    }
}
bool operator>(const BigFloat& op1,const BigFloat& op2) {
    bool tag = !(op1<=op2);
    return tag;
}
bool operator==(const BigFloat& op1,const BigFloat& op2) {
    if(op1.tag == (!op2.tag)) {
        return false;
    }
    if(op1.integer.size() != op2.integer.size() ) {
        return false;
    }
    if( op1.decimal.size() != op2.decimal.size() ) {
        return false;
    }
    vector<char>::const_iterator iter1,iter2;
    iter1 = op1.decimal.begin();
    iter2 = op2.decimal.begin();
    while( iter1!= op1.decimal.end() ) {
        if( *iter1 != *iter2 )
            return false;
        iter1++;
        iter2++;
    }
    iter1 = op1.integer.begin();
    iter2 = op2.integer.begin();
    while( iter1!= op1.integer.end() ) {
        if( *iter1 != *iter2 )
            return false;
        iter1++;
        iter2++;
    }
    return true;
}

bool operator!=(const BigFloat& op1,const BigFloat& op2) {
    return !(op1==op2);
}
bool operator>=(const BigFloat& op1,const BigFloat& op2) {
    bool tag = (op1>op2) || (op1==op2);
    return tag;
}

bool operator<=(const BigFloat& op1,const BigFloat& op2) {
    bool tag = (op1<op2) || (op1==op2);
    return tag;
}

#endif
