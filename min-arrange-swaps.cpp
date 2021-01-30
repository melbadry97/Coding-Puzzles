#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief      Wrapper for solution code
 */
class Solution {
  
private:
  
  /**
   * @brief      Finds trailing zeros.
   *
   * @param      btmx  The input bit matrix in row-major order
   *
   * @return     Array of number of trailing zeroes for each row in btmx
   * 
   * @code{.unparsed}
   *
   * allocate array for storing number of trailing zeros
   * For every row in btmx
   *   c = the last entry in the row
   *   While c is zero and we haven't run out of entries
   *     c = the next entry in the row (moving leftward)
   *   End While
   *   store the distance from c to the end of the row
   * End For  
   * Return the array of results
   * @endcode
   */
  vector<int> find_trailing_zeros(vector<vector<int>>& btmx)
  {
    int i, j;
    vector<int> trz(btmx.size());
    int c = btmx.size() - 1;
    for (i = 0; i < btmx.size(); i++)
    {
      c = btmx.size();
      while(btmx[i][--c] == 0 && c > 0);
      trz[i] = btmx.size() - c - 1;
    }
    return trz;    
  }
  
  /**
   * @brief      Moves the jth element to location i via j-i swaps.
   *
   * @param[in]  trz   The array of trailing zero counts
   * @param[in]  i     The index to move the element to
   * @param[in]  j     The index to move the element from
   *
   * @return     The number of swaps (of adjacent elements) performed
   *
   * @code{.unparsed}
   *
   * tmp = the jth element
   * While i < j
   *   move the (j-1)th element to location j
   *   increment swap count
   * End While
   * set the ith element to tmp
   * Return swap count
   * @endcode
   */
  int swap_vec(vector<int>& trz, int i, int j)
  {
    int tmp = trz[j];
    int count = j - i;
    while(i < j)
    {           
      trz[j] = trz[j - 1];
      j--;
    }
    trz[i] = tmp;
    return count;
  }
  
  /**
   * @brief      Finds the nearest row that can go at location j
   *
   * @param[in]  trz   Array of trailing zero counts
   * @param[in]  j     The index to find a row for
   *
   * @return     The index of the nearest free row that can go at index j, or -1 if no such row exists
   *
   * @code{.unparsed}
   *
   * For c = j up to the end of trz
   *   If row c has enough trailing zeros
   *     return c
   *   End If
   * End For
   * Return -1 (for now acceptable row found)
   * @endcode
   */
  int find_nearest(vector<int>& ltz, int j)
  {
    int ret = -1;
    int c = j;
    for(c = j; c < ltz.size(); c++)
    {
      if (ltz[c] >= ltz.size() - j - 1)
      {
        ret = c;
        return ret;
      }
    }
    return ret;
  }
public:
  
  /**
   * @brief      Find the minimum number of swaps needed for the bit matrix btmx
   *
   * @param      btmx  The bit matrix that needs to be rearranged
   *
   * @return     The minimum number of adjacent row swaps needed to correct btmx, or -1 if it cannot be corrected
   *
   * @code{.unparsed}
   *
   * Get number of trailing zeros in each row of btmx
   * For i = 0 to the second to last row of btmx
   *   find the nearest row to go at index i
   *   If no row is found
   *     Return -1
   *   End If
   *   move the nearest acceptable row to index i
   *   add the number of swaps required to a running total
   * End For
   * Return the total number of swaps used
   * @endcode
   */
  int minSwaps(vector<vector<int>>& btmx) {
    vector<int> trz = find_trailing_zeros(btmx);
    int count = 0;
    int i = 0;
    int tz;
    for(i = 0; i < trz.size() - 1; i++)
    {
      tz = find_nearest(trz, i);
      if (tz == -1)
      {
        return -1;
      }
      count += swap_vec(trz, i, tz);
    }
    return count;
  }
};

/**
 * @brief      Tests the solution against known cases
 *
 * @return     0
 *
 * @code{.unparsed}
 *
 * define the test case and expected output
 * run the solution
 * compare with expected output
 * print results
 * @endcode
 */
int main()
{
  vector<vector<int>> input = {{0,1,0},{1,1,0},{0,1,1}};
  int target = -1;
  Solution s;
  int output = s.minSwaps(input);

  if (output == target)
  {
    cout << "Output accepted" << endl;
  }
  else
  {
    cout << "Incorrect output" << endl;
  }

  cout << "Expected: " << target << endl;
  cout << "Recieved: " << output << endl;

  return 0;
}
