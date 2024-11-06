/*Pavithra Deepu E
S3 CSE AI 47
Java program to read and write to a file by handling all file exceptions.*/
Import java.io.FileReader;
Import java.io.FileWriter;
Import java.io.IOException;
Class file {
 Public static void main(String[] args)
 {
 Try {
 FileReader fr = new FileReader(“gfgInput.txt”);
 FileWriter fw = new FileWriter(“gfgOutput.txt”);
 String str = “”;
 Int I;
 While ((I = fr.read()) != -1) {
 Str += (char)I;
 }
 System.out.println(str);
 Fw.write(str);
 Fr.close();
 Fw.close();
 System.out.println(
 “File reading and writing both done”);
 }
 Catch (IOException e) {
 System.out.println(
 “There are some IOException”);
 }
 }
}
