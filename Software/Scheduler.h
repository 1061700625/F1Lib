#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "sys.h"
#include "delay.h"




const uint8_t SCHEDULER_MAX_TIMER_PROCS	= 4;		//��ʱ������
const uint8_t SCHEDULER_MAX_TASK	= 20;			//��ѯ����



typedef void (*timer_process_t)(void);
typedef void (*task_fn_t)(void);


typedef struct 
{
	task_fn_t function;
	uint32_t interval_micros;				//���ü��
	uint32_t max_time_micros;				//���ռ��ʱ��	
}scheduler_tasks_t;




class Scheduler
{
public:
	Scheduler(){};
	~Scheduler(){};
	
	
	void init(const scheduler_tasks_t *tasks, uint16_t num_tasks);
	void run();															//��������,���ٷ���
	

	void register_timer_process(timer_process_t proc);		//ע�ᶨʱ������
	void suspend_timer_procs(void);							//ֹͣ��ʱ������
	void resume_timer_procs(void);							//������ʱ������
	void timer_event(void);									//�ɶ�ʱ������

		
private:
	timer_process_t _timer_proc[SCHEDULER_MAX_TIMER_PROCS];	//��ʱ������
	uint16_t _num_timer_procs;
	bool _timer_suspended;			//��ͣ��ʱ�������־
	bool _in_timer_proc;			//��ʱ��������������
	bool _timer_event_missed;		//��ʧ�˶�ʱ������

	const scheduler_tasks_t *_tasks;			//�����
	uint16_t _num_tasks;						//������
	uint32_t _last_time[SCHEDULER_MAX_TASK];	//�ϴε���ʱ��
	uint32_t _time_taken[SCHEDULER_MAX_TASK];	//��������ʱ��
	int16_t _current_task;						//��ǰ��������
	
};







#endif

