This is the Sdf (Standard Delay Format) parser library used by VerilogCreator. The parser supports full IEEE 1497-2001 and generates a corresponding syntax tree. 

The library makes use of a parser generated by Coco/R based on input from EbnfStudio (see https://github.com/rochus-keller/EbnfStudio). There is no other dependency than the Qt Core library.

In order to regenerate CocoParser.cpp/h you have to use this version of Coco/R: https://github.com/rochus-keller/Coco
