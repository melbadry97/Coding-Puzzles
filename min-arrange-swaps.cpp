class Solution {
    
private:
    
    vector<int> find_trailing_zeros(vector<vector<int>>& a)
    {
        int i, j;
        vector<int> ltz(a.size());
        int c = a.size() - 1;
        for (i = a.size() - 1; i >= 0; i--)
        {
            c = a.size();
            while(a[i][--c] == 0 && c > 0);
            ltz[i] = a.size() - c - 1;
        }
        return ltz;    
    }
    
    int swap_vec(vector<int>& ltz, int i, int j)
    {
        int tmp = ltz[j];
        int count = j - i;
        while(i < j)
        {           
            ltz[j] = ltz[j - 1];
            j--;
        }
        ltz[i] = tmp;
        return count;
    }
    
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
    
    int minSwaps(vector<vector<int>>& grid) {
        vector<int> ltz = find_trailing_zeros(grid);
        int count = 0;
        int i = 0;
        int lz;
        for(i = 0; i < ltz.size() - 1; i++)
        {
            lz = find_nearest(ltz, i);
            if (lz == -1)
            {
                return -1;
            }
            count += swap_vec(ltz, i, lz);
        }
        return count;
    }
};
