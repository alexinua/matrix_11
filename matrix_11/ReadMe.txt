Problem Description: Write a threaded code that finds an example of a prime array that has the maximum number of primes hidden within it for a given array size. The following three restrictions for constructing arrays and counting primes must be observed:
1. Multiple digit prime numbers can only be constructed by reading consecutive numbers from top to bottom (vertical) or left to right (horizontal and diagonal). In the 2�2 prime array example given above, this would disqualify 31, 37, and 97 from being counted in the total. The number 73 is counted since it is read diagonally from left to right.
2. Only the digits 1..9 are to be used.
3. The total number of instances of a given digit within an array can be no more than one greater than the number of times any other digit is included. For the 2�2 case, a digit cannot appear more than once. In a 3�3 case, the following example is not considered a legitimate instance since the �1' digit appears twice, which is two more times than �8' appears (zero times).
| 1 1 3 |
| 7 5 4 |
| 9 2 6 |
Besides finding one example with the maximum number of primes that can be found contained in the array, a count of the number of other array configurations that also have the same number of primes must be computed.
Input: Two numbers will be given on the command line of the application. These will correspond to the number of rows and columns, respectively, of the array to be constructed. The range of values for both row and column values will be 1 to 10, inclusive.
Output: Output will be to stdout and must include one example of an array of the given size that contains the maximum number of hidden primes, the number of primes found in the array, a list of the primes that can be found within the printed array, and the number of total array configurations that have this maximum number of primes.
Output Example (from input �3 3'):
Example of the 3�3 case
8 2 3
4 5 7
6 1 9
20 primes are hidden in the array
{2 3 5 7 23 61 19 41 59 53 17 37 79 823 457 619 251 379 859 653 }
1 total array configurations share this maximum number of primes
Timing: The total time for execution of the application will be used for scoring. (For most accurate timing results, submission codes would include timing code to measure and print this time to stdout, otherwise an external stopwatch will be used.)