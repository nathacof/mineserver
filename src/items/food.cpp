#include "food.h"
#include "../packets.h"

bool ItemFood::affectedItem(int item)
{
  switch(item){
  case ITEM_GOLDEN_APPLE:
  case ITEM_MUSHROOM_SOUP:
  case ITEM_PORK:
  case ITEM_GRILLED_PORK:
  case ITEM_BREAD:
  case ITEM_COOKED_FISH:
  case ITEM_RAW_FISH:
  case ITEM_APPLE:
    return true;
  }
  return false;
}

void ItemFood::onRightClick(User* user, Item* item)
{
  int healammount = 0;
  switch(item->type){
  case ITEM_GOLDEN_APPLE:
    healammount = 20;
    break;
  case ITEM_MUSHROOM_SOUP:
    healammount = 10;
    break;
  case ITEM_GRILLED_PORK:
    healammount = 8;
    break;
  case ITEM_PORK:
    healammount = 3;
    break;
  case ITEM_BREAD:
    healammount = 5;
    break;
  case ITEM_COOKED_FISH:
    healammount = 5;
    break;
  case ITEM_RAW_FISH:
    healammount = 2;
    break;
  case ITEM_APPLE:
    healammount = 4;
    break;
  }
  int newhealth = user->health+healammount;
  if(newhealth > 20) 
    newhealth=20;
  user->sethealth(newhealth);
  item->count = 0; item->type=-1;
  #define INV_TASKBAR_START 36
  user->buffer << (int8_t)PACKET_SET_SLOT << (int8_t)WINDOW_PLAYER
               << (int16_t)(INV_TASKBAR_START+user->currentItemSlot())
               << (int16_t)user->inv[INV_TASKBAR_START+user->currentItemSlot()].type;
  #undef INV_TASKBAR_START

}

