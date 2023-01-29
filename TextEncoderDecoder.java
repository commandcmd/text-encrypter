import java.util.Scanner;

public class TextEncoderDecoder {
  
  public static int textEncoder(char input, int firstmultiplier, int secondmultiplier) {
    for (int i = 33; i <= 121; i += 2) {
      if (input == i)
        return (123 - input + 95) * firstmultiplier; 
    } 
    for (int i = 34; i <= 122; i += 2) {
      if (input == i)
        return (124 - input) * secondmultiplier; 
    } 
    return 100;
  }
  
  public static char textDecoder(int input, int firstmultiplier, int secondmultiplier) {
    for (int i = 33; i <= 121; i += 2) {
      if (input == (123 - i + 95) * firstmultiplier)
        return (char)i; 
    } 
    for (int i = 34; i <= 122; i += 2) {
      if (input == (124 - i) * secondmultiplier)
        return (char)i; 
    } 
    return ' ';
  }
  
  public static void main(String[] args) {

    String input = new String();
    String output = new String();

    String outputNotCompressed = new String();

    int[] inputNumConverted = new int[2048];
    int[] multiplier = new int[3];
    char separator = '°';

    Scanner in = new Scanner(System.in);

    while (true) {
      System.out.printf("Input : ");
      input = in.nextLine();

      if(input.isEmpty()){
        System.out.printf("Null input not accepted");
        continue;
      }

      if (input.charAt(0) == '~') {
        int numberConversionMemory = 0;
        int inputNumConvertedSlotMemory = 0;
        
        multiplier[1] = ((input.charAt(1) - 48) * 10 + input.charAt(2) - 48) * 10 + (input.charAt(3) - 48);
        multiplier[2] = ((input.charAt(4) - 48) * 10 + input.charAt(5) - 48) * 10 + (input.charAt(6) - 48);
        
        String inputDecompressed = new String(input);

        System.out.println("inputDecompressed = " + inputDecompressed + ", input = " + input);

        for (int j = 0; j < inputDecompressed.length(); j++) {
          if(inputDecompressed.charAt(j) == 'a'){
            switch (numberConversionMemory) {
              case 1: inputNumConverted[inputNumConvertedSlotMemory] = inputDecompressed.charAt(j - 1) - 48;break;
              case 2: inputNumConverted[inputNumConvertedSlotMemory] = (inputDecompressed.charAt(j - 2) - 48) * 10 + inputDecompressed.charAt(j - 1) - 48;break;
              case 3: inputNumConverted[inputNumConvertedSlotMemory] = ((inputDecompressed.charAt(j - 3) - 48) * 10 + inputDecompressed.charAt(j - 2) - 48) * 10 + inputDecompressed.charAt(j - 1) - 48;break;
              case 4: inputNumConverted[inputNumConvertedSlotMemory] = (((inputDecompressed.charAt(j - 4) - 48) * 10 + inputDecompressed.charAt(j - 3) - 48) * 10 + inputDecompressed.charAt(j - 2) - 48) * 10 + inputDecompressed.charAt(j - 1) - 48;break;
              case 5: inputNumConverted[inputNumConvertedSlotMemory] = ((((inputDecompressed.charAt(j - 5) - 48) * 10 + inputDecompressed.charAt(j - 4) - 48) * 10 + inputDecompressed.charAt(j - 3) - 48) * 10 + inputDecompressed.charAt(j - 2) - 48) * 10 + inputDecompressed.charAt(j - 1) - 48;break;
            } 
            inputNumConvertedSlotMemory++;
            numberConversionMemory = 0;
          } else {
            if (inputDecompressed.charAt(j) >= '0' && inputDecompressed.charAt(j) <= '9')
            numberConversionMemory++; 
          } 
        } 
        for (int j = 0; j <= inputNumConvertedSlotMemory; j++) {
          output += textDecoder(inputNumConverted[j], multiplier[1], multiplier[2]);
        } 
      } else {

        multiplier[1] = (int)Math.floor(Math.random() * 400 + 100);
        multiplier[2] = (int)Math.floor(Math.random() * 498 + 501);

        output = "~" + multiplier[1] + multiplier[2];
        outputNotCompressed = "~" + multiplier[1] + multiplier[2];

        for (int j = 0; j < input.length(); j++) {
          outputNotCompressed += textEncoder(input.charAt(j), multiplier[1], multiplier[2]);
          output += textEncoder(input.charAt(j), multiplier[1], multiplier[2]);
          outputNotCompressed += separator;
          output += separator;
        } 
      } 

      System.out.println("Output : " + output + "\nOutput not compressed : " + outputNotCompressed);

      input = "";
      output = "";
      outputNotCompressed = "";
      for (int i = 0; i < input.length(); i++) {
        inputNumConverted[i] = 0;
      } 

    } 
  }
}