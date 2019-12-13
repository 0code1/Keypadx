#define F_CPU 16000000UL
#include <stdio.h>
#include "stdio_setup.h"
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define Delay _delay_ms(50);


void Init()
{
	//input port enable pull-up
	PORTK |= (1<<PK4) | (1<<PK5) |(1<<PK6) | (1<<PK7) ;
	// OutPut
	DDRK |= (1<<PK0) | (1<<PK1) | (1<<PK2) | (1<<PK3);
}

char ColumnScan() // scan column med en static number
{ 
	PORTK |= (1<<PK0) | (1<<PK1) | (1<<PK2) | (1<<PK3); // set all port til 1 
	static columnCounter = 1; 
	
	if (columnCounter == 1)
	{
		PORTK &= ~(1<<PK0);
		columnCounter++;
		return 1;
	}
	if (columnCounter == 2)
	{
		PORTK &= ~(1<<PK1);
		columnCounter++;
		return 2;
	}
	if (columnCounter == 3)
	{
		PORTK &= ~(1<<PK2);
		columnCounter++;
		return 3;
	}
	if (columnCounter == 4)
	{
		PORTK &= ~(1<<PK3);
		columnCounter = 1;
		return 4;
	}
	
}

char ReadRows() // check if the button is push
{
	if (~PINK  & (1 << PK4)) // check om denne er blive tryk
	{
		_delay_ms(50); // delay for at denne ikke blive tryk flere gang *overflow*
		if (~PINK & (1<<PK4)) //  check igen om denne er tryk og returner værdig , denne vil stadig blive skrive om denne ikke er tryk på grund af memori før delay
		{
			return 1;
		}
	}
	if (~PINK  & (1 << PK5))
	{
		_delay_ms(50);
		if (~PINK & (1<<PK5))
		{
			return 2;
		}
	}
	if (~PINK  & (1 << PK6))
	{
		_delay_ms(50);
		if (~PINK & (1<<PK6))
		{
			return 3;
		}
	}
	if (~PINK  & (1 << PK7))
	{
		_delay_ms(50);
		if (~PINK & (1<<PK7))
		{
			return 4;
		}
	}
	return 0;
}

void DecodeKeyboard(char col , char row){
	
	char ud[4][4] = {{'D', 'C', 'B' , 'A'}, {'#', '9','6','3'},{'*','7','4','1'},{'0', '8', '5', '2'}}; // array 
	
	if (row != 0)
	{
		printf("%c\r\n", ud[col-1][row-1]); // array skal -1 da vi start på 1 og ikke 0
	}
	
	
	
}

int main(void)
{
	char column;
	char row;
	Init();
	UartInit();

	while (1)
	{
		column = ColumnScan();
		Delay;
		row = ReadRows();
		
		//test
		#pragma region test 

		//printf("kol: %d Row: %d \r\n", column , row);  // tidliger test for at fine ude af vis denne virker korrekt
		//_delay_ms(1500);
		#pragma endregion test
		
		DecodeKeyboard(column, row);
	}
}