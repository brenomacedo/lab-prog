#include <string>
#include <iostream>
#include <random>

std::random_device device;
std::mt19937 generator(device());

char gerarCaractere(char c) {
  std::uniform_int_distribution distribution('a', c);
  return distribution(generator);
}

void gerarInstanciaAleatoria(char* texto, size_t tamanhoTexto, char* padrao, size_t tamanhoPadrao, char c) {
  for (int i = 0; i < tamanhoTexto; i++) {
    texto[i] = gerarCaractere(c);
  }

  for (int i = 0; i < tamanhoPadrao; i++) {
    padrao[i] = gerarCaractere(c);
  }
}

void gerarInstanciaDePiorCaso(char* texto, size_t tamanhoTexto, char* padrao, size_t tamanhoPadrao) {
  for (int i = 0; i < tamanhoTexto; i++) {
    texto[i] = 'a';
  }

  for (int i = 0; i < tamanhoPadrao; i++) {
    padrao[i] = 'a';
  }
}

int str_len(const char* str) {
  int i = 0;
  while (true) {
    if (str[i] == '\0') return i;
    i++;
  }
}

void KMP_substr(const char* text, const char* pattern, int* resultado) {
  // computando o vetor de prefixos e sufixos
  int patLen = str_len(pattern);
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

  int j = 0;
  int k = 0;

  while (text[j] != '\0') {
    if (pattern[k] == text[j]) {
      k++, j++;
    }

    if (k == patLen) {
      resultado[positionsCount] = j - k;
      positionsCount++;

      k = a[k - 1];
    } else if (text[j] != '\0' && pattern[k] != text[j]) {
      if (k != 0) {
        k = a[k - 1];
      } else {
        j++;
      }
    }
  }

  resultado[positionsCount] = -1;

  delete a;
}

void substr(const char* text, const char* pattern, int* result) {
  int positionsCount = 0;

  for (int i = 0; text[i] != '\0'; i++) {
    bool equal = true;
    for (int j = 0; j < pattern[j] != '\0'; j++) {
      if (text[i + j] != pattern[j]) {
        equal = false;
        break;
      }
    }
    
    if (equal) {
      result[positionsCount] = i;
      positionsCount++;
    }
  }

  result[positionsCount] = -1;
}

int main(int argc, char** argv) {
  const char opt = argv[1][0];


  if (opt == 'A') {
    char letter = argv[2][0];
    size_t tamPadr = std::stol(argv[3]);
    size_t tamText = std::stol(argv[4]);  
  } else if (opt == 'P') {
    size_t tamPadr = std::stol(argv[2]);
    size_t tamText = std::stol(argv[3]);
  } else {
    size_t x = std::stoi(argv[2]);
    size_t y = std::stoi(argv[3]);
  }
}
