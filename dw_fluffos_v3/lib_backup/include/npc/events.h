#ifndef __NPC_EVENTS_H__
#define __NPC_EVENTS_H__
#define EVENT_LOSE_HPS "lose hps"
#define EVENT_GAIN_HPS "gain hps"
#define EVENT_FULLY_HEALED "100% hps"
#define EVENT_75PERCENT_HPS "75% hps"
#define EVENT_50PERCENT_HPS "50% hps"
#define EVENT_25PERCENT_HPS "25% hps"
#define EVENT_MOVED "moved"
#define EVENT_GIVEN "given"
#define EVENT_PLAN_FINISHED_TAG "plan finished : "
#define EVENT_PLAN_FINISHED(PLAN) (EVENT_PLAN_FINISHED_TAG + PLAN)
#endif