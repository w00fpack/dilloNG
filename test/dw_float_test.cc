#include <fltk/Window.h>
#include <fltk/run.h>

#include "../dw/core.hh"
#include "../dw/fltkcore.hh"
#include "../dw/fltkviewport.hh"
#include "../dw/textblock.hh"

using namespace dw;
using namespace dw::core;
using namespace dw::core::style;
using namespace dw::fltk;

static Textblock *firstFloat;
static Style *wordStyle;

static void addTextToFloatTimeout (void *data)
{
   printf("addTextToFloatTimeout\n");

   char *fWords[] = { "This", "is", "a", "float,", "which", "is",
                      "set", "aside", "from", "the", "main",
                      "text.", NULL };
	
   for(int k = 0; fWords[k]; k++) {
      firstFloat->addText(strdup(fWords[k]), wordStyle);
      firstFloat->addSpace(wordStyle);
   }
   
   firstFloat->flush();

   ::fltk::repeat_timeout (2, addTextToFloatTimeout, NULL);
}

int main(int argc, char **argv)
{
   FltkPlatform *platform = new FltkPlatform ();
   Layout *layout = new Layout (platform);

   ::fltk::Window *window = new ::fltk::Window(400, 600, "Dw Floats Example");
   window->begin();

   FltkViewport *viewport = new FltkViewport (0, 0, 400, 600);
   layout->attachView (viewport);

   StyleAttrs styleAttrs;
   styleAttrs.initValues ();
   styleAttrs.margin.setVal (5);

   FontAttrs fontAttrs;
   fontAttrs.name = "Bitstream Charter";
   fontAttrs.size = 14;
   fontAttrs.weight = 400;
   fontAttrs.style = FONT_STYLE_NORMAL;
   styleAttrs.font = Font::create (layout, &fontAttrs);

   styleAttrs.color = Color::createSimple (layout, 0x000000);
   styleAttrs.backgroundColor = Color::createSimple (layout, 0xffffff);

   Style *widgetStyle = Style::create (layout, &styleAttrs);

   styleAttrs.borderWidth.setVal (1);
   styleAttrs.setBorderColor (Color::createShaded (layout, 0x808080));
   styleAttrs.setBorderStyle (BORDER_DASHED);
   styleAttrs.width = createAbsLength(100);
   styleAttrs.vloat = FLOAT_LEFT;
   Style *leftFloatStyle = Style::create (layout, &styleAttrs);
   
   styleAttrs.width = createAbsLength(80);
   styleAttrs.vloat = FLOAT_RIGHT;
   Style *rightFloatStyle = Style::create (layout, &styleAttrs);

   Textblock *textblock = new Textblock (false);
   textblock->setStyle (widgetStyle);
   layout->setWidget (textblock);

   widgetStyle->unref();

   styleAttrs.borderWidth.setVal (0);
   styleAttrs.width = LENGTH_AUTO;
   styleAttrs.vloat = FLOAT_NONE;
   styleAttrs.margin.setVal (0);
   styleAttrs.backgroundColor = NULL;

   wordStyle = Style::create (layout, &styleAttrs);

   for(int i = 1; i <= 10; i++) {
      char buf[4];
      sprintf(buf, "%d%s",
              i, (i == 1 ? "st" : (i == 2 ? "nd" : (i == 3 ? "rd" : "th"))));

      char *words[] = { "This", "is", "the", buf, "paragraph.",
                        "Here", "comes", "some", "more", "text",
                        "to", "demonstrate", "word", "wrapping.",
                        NULL };

      for(int j = 0; words[j]; j++) {
         textblock->addText(strdup(words[j]), wordStyle);
         textblock->addSpace(wordStyle);
         
         if ((i == 3 || i == 5) && j == 8) {
         	textblock->addText(strdup("[float]"), wordStyle);
            textblock->addSpace(wordStyle);
         
            Textblock *vloat = new Textblock (false);
            textblock->addFloatIntoGenerator(vloat, i == 3 ? leftFloatStyle : rightFloatStyle);
            
            char *fWords[] = { "This", "is", "a", "float,", "which", "is",
                               "set", "aside", "from", "the", "main",
                               "text.", NULL };

            for(int k = 0; fWords[k]; k++) {
               vloat->addText(strdup(fWords[k]), wordStyle);
               vloat->addSpace(wordStyle);
            }
            
            vloat->flush ();
            
            if(i == 3)
               firstFloat = vloat;
         }
      }

      textblock->addParbreak(10, wordStyle);
   }

   leftFloatStyle->unref();
   rightFloatStyle->unref();

   textblock->flush ();

   window->resizable(viewport);
   window->show();
   ::fltk::add_timeout (2, addTextToFloatTimeout, NULL);
   int errorCode = ::fltk::run();

   wordStyle->unref();
   delete layout;

   return errorCode;
}