class Solution {
public:
    bool checkWord(vector<vector<char> > &board, string word, int x, int y, 
        int index, int h, int w, int len) {
        if( board[x][y] != word[index] ) return false;
        board[x][y] = '#';
        if( index == len-1 ) return true;
        if( x < h-1 && checkWord(board, word, x+1, y, index+1, h, w, len) ) return true;
        if( y < w-1 && checkWord(board, word, x, y+1, index+1, h, w, len) ) return true;
        if( x > 0 && checkWord(board, word, x-1, y, index+1, h, w, len) ) return true;
        if( y > 0 && checkWord(board, word, x, y-1, index+1, h, w, len) ) return true;
        return false;
    }
    bool exist(vector<vector<char> > &board, string word) {
        int h = board.size();
        int len = word.length();
        if( len == 0 ) return true;
        if( h == 0 ) return false;
        int w = board[0].size();
        for( int i = 0; i < h; i++ ) {
            for( int j = 0; j < w; j++ ) {
                if( board[i][j] != word[0] ) continue;
                vector<vector<char> > tmp (board);
                if( checkWord(tmp, word, i, j, 0, h, w, len) ) return true;
            }
        }
        return false;
    }
};