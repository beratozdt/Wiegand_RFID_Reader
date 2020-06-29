#define MAX_LENGTH 50
#define WEIGAND_WAIT_TIME  3000
#define D0 2
#define D1 3
 
unsigned char buffer_data[MAX_LENGTH];
unsigned char bit_count;
unsigned char flag;
unsigned int wiegand_counter;
unsigned int i;
unsigned long facility_code=0;
unsigned long card_code=0;
unsigned long id_code=0;
 

void D0_read()
{
  bit_count++;
  flag = 0;
  wiegand_counter = WEIGAND_WAIT_TIME;
 
}
 

void D1_read()
{
  buffer_data[bit_count] = 1;
  bit_count++;
  flag = 0;
  wiegand_counter = WEIGAND_WAIT_TIME;
}
 
void setup()
{
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  attachInterrupt(0, D0_read, FALLING);
  attachInterrupt(1, D1_read, FALLING);
  Serial.begin(9600);
  wiegand_counter = WEIGAND_WAIT_TIME;
}
 
void loop()
{
  
  if (!flag) {
    if (--wiegand_counter == 0)
      flag = 1; 
  }

  
  if (bit_count > 0 && flag) {
    
    
    if (bit_count == 34)
    { 
      for (i=1; i<33; i++)
      {
         id_code <<=1;
         id_code |= buffer_data[i];
      }

      for (i=1; i<14; i++)
      {
         facility_code <<=1;
         facility_code |= buffer_data[i];
      }
      for (i=14; i<33; i++)
      {
         card_code <<=1;
         card_code |= buffer_data[i];
      }
      Serial.print("Binary:");
      for (i=0; i<33; ++i)
      Serial.print(buffer_data[i]);
      
      Serial.println(" ");
      Serial.print("Kart ID:");
      Serial.println(id_code);
    }
     delay(100);
     bit_count = 0;
     facility_code = 0;
     card_code = 0;
     id_code = 0;
     for (i=0; i<MAX_LENGTH; i++)
     {
       buffer_data[i] = 0;
     }

  }
}
