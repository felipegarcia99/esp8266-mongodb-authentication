void center_text(String part, int line){
  int avr = calculate_center_pos(part.length());
  lcd.setCursor(avr, line);
  lcd.print(part);
}

int calculate_center_pos(int length){
  int dif = 16 - length;
  float tempavr = dif/2;
  int avr = static_cast<int>(tempavr);
  return avr;
}

String* string_split(String text, String *parts){
  int len = text.length();
  String part1 = "";
  String part2 = "";
  bool flag = true;
  
  for (int i = 0; i < len; i++){
    if (text.charAt(i) == '\n'){
      flag = false;
      continue;
    }
    
    if (flag){
      part1.concat(text.charAt(i));
    }
    else{
      part2.concat(text.charAt(i));
    }
  }
  
  parts[0] = part1;
  parts[1] = part2;
  return parts;
}