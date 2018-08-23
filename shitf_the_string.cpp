#import <iostream>
#import <string>
#import <vector>

// Implementation of KPM "Compute prefix function"
using namespace std;

vector<int> preprocess(string& pattern)
{
  vector<int> next(pattern.size() + 1, 0);
  int j = 0;
  
  next[1] = 0;
  for (int i = 2; i < pattern.size() + 1; i++) {
    int idx = i - 1;
    
    while (pattern[idx] != pattern[j] && j > 0) {
      j = next[j];
    }
    if (pattern[idx] == pattern[j])
      j = j + 1;
    next[i] = j;
  }
  // for (auto it = next.begin(); it != next.end(); it++) {
  //   cout << "next[" << next.size() - (next.end() - it) << "]=" << *it << endl;
  // }
  return next;
}

int kpm(string text, string pattern)
{
  vector<int> next = preprocess(pattern);

  int ch, max, index;
  max = ch = index = 0; // Char matched

  for (int i = 0; i < text.size(); i++) {
    while (ch > 0 && pattern[ch] != text[i])
      ch = next[ch];

    if (pattern[ch] == text[i])
	ch = ch + 1;

    if (ch > max) {
      max = ch;
      index = i - ch;
    }
    
    if (ch == pattern.size()) {
      cout << "Pattern " << pattern << " matched in " << text << endl;
      ch = next[ch];
    }
  }
  return index;
}
  
int main()
{
  int size;
  string input, pattern;
  
  cin >> size;
  cin >> pattern >> input;

  cout << kpm(input, pattern) + 1 << endl;
  return 0;
}

