# include <stdio.h>

unsigned long value = 0b00000000000000000000000011100111;

union Endian{
  unsigned int X;
  unsigned char Array[sizeof(int)];    
};

/**
@brief Seta o bit da posição de memória apontada por p
@param p Ponteiro para variável de 32bits cujo bit será setado
@param bitn Posição do bit (0 a 31) a ser setado
*/
void SetBit(unsigned long *p, unsigned char bitn) {  

	*p = *p | (1<<bitn);
  }

/**
@brief Reseta o bit da posição de memória apontada por p
@param p Ponteiro para variável de 32bits cujo bit será resetado
@param bitn Posição do bit (0 a 31) a ser resetado
*/
void ResetBit(unsigned long *p, unsigned char bitn) {  

*p = *p & ~(1<<bitn);

  }

/**
@brief Inverte um bit da posição de memória apontada por p
@param p Ponteiro para variável de 32bits cujo bit será invertido
@param bitn Posição do bit (0 a 31) a ser invertido
*/
void ToggletBit(unsigned long *p, unsigned char bitn) {  

 *p = *p ^(1<<bitn);

  }

/**
@brief Ler o bit da posição de memória apontada por p
@param p Ponteiro para variável de 32bits cujo bit será lido
@param bitn Posição do bit (0 a 31) a ser lido
@return retorna o estado (0 ou 1) do bit da posição de memória apontada por p
*/
unsigned char  ReadBit(unsigned long *p, unsigned char bitn) {  

	return ((*p & (1<<bitn))? 1 : 0);
  }

/**
@brief Ler uma fatia de bits da posição bitstart até bitend
@param p Ponteiro para variável de 32bits de onde a fatia  de bits será lida
@param bitstart Posição do bit (0 a 31) do primeiro bit a ser lido
@param bitend Posição do bit (0 a 31) do último bit a ser lido
@return retorna os bits de bitstart até bitend
*/
unsigned long  ReadBitSlice(unsigned long *p, unsigned char bitstart, unsigned char bitend) {  
		
		unsigned long aux=0b0;
		
		for(int i=bitstart;i<=bitend;i++)
		{
			aux = aux | ReadBit(p,i)<<i;
		}

		return aux;
  }

/**
@brief Detecta se a arquitetura corrente armazena os dados  em formato little endian ou big endian
@return Retorna 1 para Little endian e 0  para Big Endian
*/
unsigned char isLittleEndian (void) {
  volatile union Endian Test;
    
  Test.X = 1;
    
  if(Test.Array[0] == 1){
    return 1;
  } else {
    return 0;
  }
}

/**
@brief mostra na tela os bits do binário apontado por p
@param p Ponteiro para variável de 32bits que será mostrada na tela
*/
void showBits(unsigned long *p)
{
	int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(*p & (1 << i) ? '1' : '0');
    }
    printf("\n");
}

/**
@brief mostra na tela a fatia de bits gerada por ReadBitSlice
@param p Ponteiro para variável de 32 bits
@param bitstart Posição do bit (0 a 31) do primeiro bit a ser lido
@param bitend Posição do bit (0 a 31) do último bit a ser lido
*/
void showBitSlice(unsigned long *p,unsigned char bitstart, unsigned char bitend)
{
  
  for(int i=bitend;i>=bitstart;i--)
  {
    putchar(*p & (1 << i) ? '1' : '0');
  }
  printf("\n");
}

int main(){

showBits(&value);
SetBit(&value,12);
showBits(&value);
ResetBit(&value,12);
showBits(&value);
ToggletBit(&value,15);
showBits(&value);
printf("%u\n",ReadBit(&value,2));
unsigned long bitSlice = ReadBitSlice(&value,5,15);
showBitSlice(&bitSlice,5,15);
printf("%d\n", isLittleEndian());


	return 0;
}
