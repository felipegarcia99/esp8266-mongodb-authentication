void lcd_init(){
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
}

void lcd_pretty_print(String text){
  lcd.clear();
  
  //split string
  //solução para o problema do retorno do array:
  //https://www.geeksforgeeks.org/return-local-array-c-function/
  //(Using Dynamically Allocated Array)
  String arr[2];
  String *parts= string_split(text, arr);

  center_text(parts[0], 0);
  center_text(parts[1], 1);
}
