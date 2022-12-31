#include "lib/pdfgen.h"
#include <iostream>

int main() {
  // Create PDFGen instance
  PDFGen pdfgen("hi.pdf", 210, 297);

  // Add some text to the PDF document
  //pdfgen.add_text(0.0, 60.0, "Lukáš + Ema =", 20, "res/fonts/Ubuntu-Medium.ttf");
  pdfgen.add_text(20, 5, "Marie Mitášová",  5, "res/fonts/Ubuntu-Medium.ttf");
 // pdfgen.add_latex(0, 30, "F = ma");
  //pdfgen.add_image(0, 100, "res/img/spotify.png");
  pdfgen.save_pdf();
//y = 50,x=20
  return 0;
}