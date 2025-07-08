/*************************************************************************************************************
*  Math Library : Design and implement a versatile numeric library utilizing the power of Modern C++ templates
*  This library handle ( sum - sub - min - max ) Methods using concept of templates 
****************************************************************************************************************/

/* File Guarding */

#ifndef _MATH_HPP
#define _MATH_HPP

/* Include Dependancies */
#include <type_traits>
#include <string>

/* Create New Scope using namespace to avoid any confilicts with another libs */
namespace lib {

/* (-) Operator Overloading for string data types */
int operator-(const std::string & a , const std::string & b){

    return a.length() - b.length();
}

/* (+) Operator Overloading for string data types */
int operator+(const std::string & a , const std::string & b){

    return a.length() + b.length();
}
/*************************************  1- Sum Method ************************************************************************* */
/* Description :
   implement sum Function handle to hnalde zero argument case 
*/
inline auto sum (){

    return 0;
}
/* Description :
   Using Templates : implement sum function to handle one argument case.
*/
template < typename T >
auto sum (const T & a ){

    return a;

}
/* Description :
   using variadic templates ( Folding Expression ) and type-trais : 
   implement sum Function take two or more arguments with basic arthimetic data types .
   return auto (To control ordering of data types and return valid value ) .
*/
template < typename T , typename U , typename ... Ts>
auto sum (const T & a , const U & b , const Ts & ... values ){
    
    /* static_assert : evaluate (True) if all data types is arth 
                                (False) if using another data types -- Print error message 
    */
   static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>,"Arguments must be numeric types (integer or floating-point)");

    /* Apply Folding Expression*/
    auto r = a + b;  
    return r + sum(values ...);

}
/* Description : 
    Template specialization for String data type 
*/
template <>
auto sum <std::string , std::string>(const std::string & a , const std::string & b){
    
    return a+b;

}

/*************************************  2- Sub Method ************************************************************************* */
/* Description :
   implement sub Function handle to hnalde zero argument case 
*/
inline auto sub (){

    return 0;
}
/* Description :
   Using Templates : implement sub function to handle one argument case.
*/
template < typename T >
auto sub (const T & a ){

    return a;

}
/* Description :
   using variadic templates ( Folding Expression ) and type-trais : 
   implement sub Function take two or more arguments with basic arthimetic data types .
   return auto (To control ordering of data types and return valid value ) .
*/
template < typename T , typename U , typename ... Ts>
auto sub (const T & a , const U & b , const Ts & ... values ){
    
    /* static_assert : evaluate (True) if all data types is arth 
                                (False) if using another data types -- Print error message 
    */
   static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>,"Arguments must be numeric types (integer or floating-point)");

    /* Apply Folding Expression*/
    auto r = a - b;  
    return (sub(r,values...));

}
/* Description : 
    Template specialization for String data type 
*/
template <>
auto sub <std::string, std::string> (const std::string & a , const std::string & b){
    
    return a-b;

}
/*************************************  3-Max Method ************************************************************************* */
/* Description :
   implement max Function handle to hnalde zero argument case 
*/
inline auto max (){
    return 0;
}

/* Description :
   Using Templates : implement max function to handle one argument case.
*/
template < typename T >
auto max (const T & a){

    return a;
}

/* Description :
   using variadic templates ( Tail Recursion) and type-trais : 
   implement max Function take two or more arguments with integral data types .
   return auto (To control ordering of data types and return valid value ) .
*/
template <typename T , typename U , typename ... Ts>
auto max (const T & a , const U & b , const Ts & ... values){

    /* static_assert : evaluate (True) if all data types is integral 
                                (False) if using another data types -- Print error message 
    */
   static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>,"Arguments must be numeric types (integer or floating-point)");
    /* Using Tail Recusion :
       Check Number of arguments to decide if recurive or return max 
    */
    if constexpr (sizeof ...(Ts) > 0){

        auto max_v = a;
        if (b > max_v)
           max_v = b;
        return max(max_v,values...);

    } else  {
        auto max_v = a ;
        if (b > max_v)
          max_v = b;
        return max_v;
    }

}
/***************************************** 4-Min Method ************************************************************************* */
/* Description :
   implement min Function handle to hnalde zero argument case 
*/
inline auto min (){
    return 0;
}

/* Description :
   Using Templates : implement min function to handle one argument case.
*/
template < typename T >
auto min (const T & a){

    return a;
}

/* Description :
   using variadic templates ( Tail Recursion) and type-trais : 
   implement min Function take two or more arguments with integral data types .
   return auto (To control ordering of data types and return valid value ) .
*/
template <typename T , typename U , typename ... Ts>
auto min (const T & a , const U & b , const Ts & ... values){

    /* static_assert : evaluate (True) if all data types is integral 
                                (False) if using another data types -- Print error message 
    */
   static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>,"Arguments must be numeric types (integer or floating-point)");

    /* Using Tail Recusion :
       Check Number of arguments to decide if recurive or return min 
    */
    if constexpr (sizeof ...(Ts) > 0){

        auto min_v = a;
        if (b < min_v)
           min_v = b;
        return min(min_v,values...);

    } else  {
        auto min_v = a ;
        if (b < min_v)
          min_v = b;
        return min_v;
    }
}

}

#endif