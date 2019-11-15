#ifndef __PROCESS_H
#define __PROCESS_H

#include <mmu_pagging.h>
#include <stdbool.h>
#include <stdint.h>

#define PROCESS_ATTR_USER_SPACE		0x0001
#define PROCESS_ATTR_KERNEL_SPACE	0x0002

#define PROCESS_STATE_READY       1
#define PROCESS_STATE_WAIT        2
#define PROCESS_STATE_RUNNING     3

#define KERNEL_STACK_SIZE 2048

typedef struct {
    uint32_t reserved0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1;
    uint64_t ist1; 
    uint64_t ist2; 
    uint64_t ist3; 
    uint64_t ist4; 
    uint64_t ist5; 
    uint64_t ist6; 
    uint64_t ist7; 
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iomap_base;
} __attribute__((packed)) tss_t;

extern tss_t tss64; // from: loader.asm

typedef struct task_struct {
  uint64_t rsp;
  uint32_t id;
  uint16_t attribute;
  uint16_t state;
  uint8_t kstack[KERNEL_STACK_SIZE];
  // For now we are supporting only 2MB programs :) 
  // We keep track of one entry in PDE that will be mapped to 0x0000000 (user program space)
  pde_t pde[512]; 
  // Win manager reference if any
  void* window;
  struct task_struct* next;
  struct task_struct* prev;
}  __attribute__((packed)) task_t;

extern task_t *task_list_head;
extern task_t *task_list_last;
extern task_t *task_list_current;

bool task_list_is_empty();
int task_list_length();
task_t* task_list_insert(task_t* new_task);
void task_list_delete(task_t* task);
void task_list_dump();

void create_kernel_process(void* entry_point);
void create_user_process(void* elf_raw_data);
void kill_process(task_t* task);

task_t* next_task();
task_t* current_task();
void __switch_to(task_t* next);
void do_first_task_jump();
void schedule();
#endif