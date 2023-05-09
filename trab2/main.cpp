#include <string>
#include <iostream>

int* KMP_substr(const std::string& text, const std::string& pattern) {
  // computando o vetor de prefixos e sufixos
  int patLen = pattern.length();
  int txtLen = text.length();
  int* a = new int[patLen];

  int l = 0;
  a[0] = 0;
  int i = 1;
  while (i < patLen) {
    if (pattern[i] == pattern[l]) {
      l++;
      a[i] = l;
      i++;
    } else {
      if (l != 0) {
        l = a[l - 1];
      } else {
        a[i] = 0;
        i++;
      }
    }
  }

  int positionsCount = 0;
  int* foundPositions = new int[txtLen - patLen];
  int j = 0;
  int k = 0;

  while ((txtLen - j) >= (patLen - k)) {
    if (pattern[k] == text[j]) {
      k++, j++;
    }

    if (k == patLen) {
      foundPositions[positionsCount] = j - k;
      positionsCount++;

      k = a[k - 1];
    } else if (j < txtLen && pattern[k] != text[j]) {
      if (k != 0) {
        k = a[k - 1];
      } else {
        j++;
      }
    }
  }

  foundPositions[positionsCount] = -1;

  delete a;
  return foundPositions;
}

int* substr(const std::string& text, const std::string& pattern) {
  int txtLen = text.length();
  int patLen = pattern.length();

  int* foundPositions = new int[txtLen - patLen];
  int positionsCount = 0;

  for (int i = 0; i <= (txtLen - patLen); i++) {
    bool equal = true;
    for (int j = 0; j < patLen; j++) {
      if (text[i + j] != pattern[j]) {
        equal = false;
        break;
      }
    }
    
    if (equal) {
      foundPositions[positionsCount] = i;
      positionsCount++;
    }
  }

  foundPositions[positionsCount] = -1;
  return foundPositions;
}

int main() {
  std::string text = "brenomacedodebrito";
  std::string pattern = "macedo";

  int foundPatterns = text.length() - pattern.length() + 1;
  int* fP = substr(text, pattern);

  for (int i = 0; i < foundPatterns; i++) {
    std::cout << fP[i] << std::endl;
  }
}
