#include "nn_demo.h"
#include "dataset.h"

#include <lcd.h>
#include <terminal.h>
#include <timer.h>

NNDemo::NNDemo()
{
  item_idx = 0;
  correct  = 0;
  wrong    = 0;
}

NNDemo::~NNDemo()
{

}

void NNDemo::main()
{
  terminal << "computing\n";

  network_set_input(item_idx);

  unsigned long long int time_start = timer.get_time();

  nn.forward();
  nn_result = nn.class_result();

  unsigned long long int time_stop = timer.get_time();

  if (nn_result == labels[item_idx])
    correct++;
  else
    wrong++;
  duration = time_stop - time_start;

  show_dataset_item(item_idx);
  show_result();
  lcd.Refresh();


  item_idx = (item_idx + 1)%DATASET_COUNT;
}


void NNDemo::show_dataset_item(unsigned int idx)
{
  unsigned char *item = get_dataset_item(idx);

  unsigned int ptr = 0;

  unsigned int x_ofs = lcd.get_height()/2 - DATASET_HEIGHT/2;
  unsigned int y_ofs = 50 + lcd.get_width()/4  - DATASET_WIDTH/2;

  for (unsigned int x = 0; x < DATASET_WIDTH+2; x++)
  {
    lcd.DrawPixel(x + x_ofs - 1, -1 + y_ofs, 255, 255, 255);
    lcd.DrawPixel(x + x_ofs - 1, DATASET_HEIGHT + y_ofs, 255, 255, 255);
  }

  for (unsigned int y = 0; y < DATASET_HEIGHT+2; y++)
  {
    lcd.DrawPixel(-1 + x_ofs, y + y_ofs - 1, 255, 255, 255);
    lcd.DrawPixel(DATASET_WIDTH + x_ofs, y + y_ofs - 1, 255, 255, 255);
  }

  for (unsigned int y = 0; y < DATASET_HEIGHT; y++)
    for (unsigned int x = 0; x < DATASET_WIDTH; x++)
    {
      uint8_t r, g, b;

      if (DATASET_CHANNELS == 3)
      {
        r = item[ptr + 0];
        g = item[ptr + 1];
        b = item[ptr + 2];
        ptr+=3;
      }
      else
      {
        r = item[ptr];
        g = item[ptr];
        b = item[ptr];
        ptr++;
      }

      lcd.DrawPixel(x + x_ofs, y + y_ofs, r, g, b);
    }
}




void NNDemo::show_result()
{
  terminal << "correct " << correct << ", wrong " << wrong << ", time " << duration << " [ms]\n";

  lcd.Puts(0, 0, "dense neural network demo", 255, 255, 255);
  lcd.Puts(0, 20, "network answer", 255, 200, 0);    lcd.PutInt(250, 20, nn_result);
  lcd.Puts(0, 40, "Correct", 0, 255, 0);            lcd.PutInt(250, 40, correct);
  lcd.Puts(0, 60, "Wrong", 255, 0, 0);              lcd.PutInt(250, 60, wrong);
  lcd.Puts(0, 80, "Time [ms]", 255, 255, 255);      lcd.PutInt(250, 80, duration);

}

unsigned char* NNDemo::get_dataset_item(unsigned int idx)
{
  return (unsigned char*)(dataset + idx*DATASET_WIDTH*DATASET_HEIGHT*DATASET_CHANNELS);
}

void NNDemo::network_set_input(unsigned int idx)
{
  unsigned char *item = get_dataset_item(idx);
  for (unsigned int i = 0; i < nn.input_size(); i++)
  {
    int v = item[i]/2;
    nn.get_input()[i] = v;
  }
}
