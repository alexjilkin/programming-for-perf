#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "include/fast.hpp"

/**
 * Helper function to ouput usage information when the -h flag is detected
 */
void help() {
  std::cout << R"(
Program to test set data structures for positive ints.

usage:
    ./query [options] [input file]

Options:\n
-h             Outputs this message and terminates.
-t <number>    Type. 1 will use std::set, 2 will use std::unordered_set.
               Other options will be implementation dependent.
-l <number>    Limit. Highest number that will be inserted. Defaults to 2^31 - 1.
-s             If given, it will be assumed that all insertions will be done before any queries.
-v             Verify that the datastructure behaves the same way as std::unordered_set (slow).
-d             Debug mode. Run the program in interactive / verbose mode.
<input file>   Specify file to read insertions and queris from.
               If no input file is specified standard input will be used.

Accepted input is a sequence of non-negative integers in the [0..<limit>] range, with negative
integers switching between insertion and query modes. The program  will start in insert mode.

Examples:
   ./query -t 3 -d
         Interactively test the type 3 data structure (unbalanced binary tree by default).

   /usr/bin/time ./query -t 2 data.txt >> /dev/null
         Benchmark std::unordered set with operations from the data.txt file.

   /usr/bin/time ./query -s -l 10000 limited_sorted.txt >> /dev/null
         Benchmark data with guaranteed sorted and limited input sequence.
         Allows program logic to select data structure type.)"
            << std::endl;
}

/**
 * Executes operations on compatible data structures. Optionally validating the
 * data structure outputs with std::unordered_set.
 *
 * Class template parametes work similarly to generics in java or object
 * polymorphism in python. Here the query_structure template essentially states
 * that the first input parameter to the function is a pointer to a compatible
 * data structure that supports insert and contains operations for integers.
 *
 * Other types of template parameters allow conditional compilation of the input
 * function based on the template parameter value. For example here the validate
 * parameter along with "if constexpr" allows the compiler to compile separate
 * versions of the functions for both different values of validate if required.
 *
 * There is no (or almost no) performance penalty for template use in c++. A
 * completely separate version of the function is compiled for each possible
 * combination of template parameters. If 5 different query structures are
 * supported, along with the two values for validate, a total of 10 different
 * versions of "run_ops" will be compiled in the final binary. This does have
 * some minor performance implications but significantly less than java generic
 * or object polymorphism.
 *
 * @tparam query_structure Type of query strucure.
 * @tparam validate        Should query_structure operations be validated.
 *
 * @param qs    Pointer to query structure to use.
 * @param in    Input stream to use for retreaving operations.
 */
template <class query_structure, bool debug = false, bool validate = false>
void run_ops(query_structure &qs, std::istream &in) {
  std::ios_base::sync_with_stdio(false);
  int val;
  bool insert = true;
  while (in >> val) {
    if (val >= 0) {
      if (insert) {
        qs.insert(val);
      } else {
        std::cout << qs.count(val) << '\n';
      }
    } else {
      insert = !insert;
    }
  }
}

template <bool debug = false, bool verify = false>
void select_qs(std::istream &in) {

  pfp::fast<uint32_t> v;
  run_ops<pfp::fast<uint32_t>, debug, verify>(v, in);
}

int main(int argc, char const *argv[]) {
//   int type = 0;
  int input_file = 0;
  int i = 1;
  while (i < argc) {
    std::string s(argv[i++]);
    if (s.compare("-t") == 0) {
      i++;
    } else {
      input_file = i - 1;
    }
  }

  if (input_file > 0) {
    std::ifstream in(argv[input_file]);

    select_qs<false, false>(in);
  } else {
    select_qs<false, false>(std::cin);
  }
  return 0;
}