/*==================================
TSN2101 Operating Systems

Sections: TC101, TC202

====================================*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <windows.h>
#include<cstdlib>
#include <ctime>
using namespace std;

bool executingSRTN = false, executingSJFP = false, executingTQS = false, executingLS = false;

class Process {
  string processName;
  int arrivalTime;
  int burstTime;
  int priority;
  int remainingTime;
  int timeRR;
  vector<int> ticket;
  
  int finishTime;
  int turnaroundTime;
  int waitingTime;
  
  int queue;
  
  public:
  Process()
  { }
  
  Process(string name, int arrival, int burst, int priority)
  : processName(name), arrivalTime(arrival), burstTime(burst), priority(priority)
  {
    remainingTime = burst;
    //cout << "A process has been created.";
  }
  ~Process(){ }
  
  int getQueue()
  {
    return queue;
  }
  
  void setQueue(int n)
  {
    queue = n;
  }
  void calcTurnaroundTime()
  {
    turnaroundTime = finishTime - arrivalTime;
  }
  
  void calcWaitingTime()
  {
    waitingTime = turnaroundTime - burstTime;
  }
  
  void setFinishTime(int time)
  {
    finishTime = time;
  }
  
  int getFinishTime()
  {
    return finishTime;
  }
  
  void setTurnaroundTime(int time)
  {
    turnaroundTime = time;
  }
  
  int getTurnaroundTime()
  {
    return turnaroundTime;
  }
 
  int getWaitingTime()
  {
    return waitingTime;
  }
  
  void setWaitingTime(int time)
  {
    waitingTime = time;
  }
 
  
  
  vector<int> getTicket()
  {
    return ticket;
  }
  
  void setTicket(int num)
  {
    ticket.push_back(num);
  }
  
  void deleteTicket(int num)
  {
    for(int i = 0; i < ticket.size(); i++)
    {
      if (ticket[i] == num)
      {
        ticket.erase( ticket.begin() + i);
      }
    }
  }
  
  void deleteAllTicket()
  {
    for(int i = 0; i < ticket.size(); i++)
    {
      ticket.pop_back();
    }
  }
  string getName()
  {
    return processName;
  }
  
  void setName(string name)
  {
    processName = name;
  }
  
  void setArrival(int time)
  {
    arrivalTime = time;
  }
  void setBurst(int time)
  {
    burstTime = time;
  }
  void setPriority(int time)
  {
    priority = time;
  }
  int getArrival()
  {
    return arrivalTime;
  }
  
  int getBurst()
  {
    return burstTime;
  }
  
  int getPriority()
  {
    return priority;
  }
  
  int getRemaining()
  {
    return remainingTime;
  }
  
  void setRemaining(int remain)
  {
    remainingTime = remain;
  }
  
  int getRR()
  {
    return timeRR;
  }
  
  void setRR(int time)
  {
    timeRR = time;
  }
  
   // Process& operator= (Process process)
   // {
      // if(this!=&process)
      // {
         // processName = process.getName();
         // arrivalTime = process.getArrival();
         // burstTime = process.getBurst(); 
         // priority = process.getPriority();
         // remainingTime = process.getRemaining();
         // timeRR = process.getRR();
         
         // deleteAllTicket();
         
         // for(int i = 0; i < process.getTicket().size(); i++)
         // {
            // setTicket( process.getTicket()[i] );
         // }
      // }
      // return *this;
   // }
   
  bool operator< (Process second) const
  {
    if(executingSRTN == true)
      return remainingTime < second.getRemaining();
    else if (executingSJFP == true)
      return priority < second.getPriority();
    else if (executingTQS == true)
      return arrivalTime < second.getArrival();
  }
  
};

void displayProcess(vector<Process> processes)
{
  if(processes.size() != 0)
  {
    cout << " +---------------------------------------------+" << endl;
    cout << " | Processes:                                  |" << endl;
    cout << " +------+--------------+------------+----------+" << endl;
    cout << " | Name | Arrival Time | Burst Time | Priority |" << endl;
    cout << " +------+--------------+------------+----------+" << endl;
    for(int i = 0; i < processes.size(); i++)
      cout << " | " <<setw(3) << processes[i].getName() << "  |      " <<  setw(2) << setfill(' ') << processes[i].getArrival() << "      |     " 
           << setw(2) << setfill(' ') << processes[i].getBurst() << "     |    " << setw(2) << setfill(' ') << processes[i].getPriority() << "    |   " <<endl;
    cout << " +------+--------------+------------+----------+" << endl << endl;
  }
  else
  {
    cout << " No process has been initialized." << endl << endl;
  }
  system("pause");
}

void initialize(vector<Process>& processes)
{
  processes.clear();

  int processNum, arrival, burst, priority;
  cout << " How many processes are there? => ";
  cin >> processNum;
  cout << endl;
  
  if(processNum < 3 || processNum > 10)
  {
    cout << " The number must be ranged from 3 to 10." << endl;
    return;
  }
  for(int i = 0; i < processNum; i++)
  {
    arrival = burst = priority = 0;
    cout << " Process " << i+1 << ": " << endl;
    cout << "    Arrival Time => ";
    cin >> arrival;
    cout << "    Burst Time => ";
    cin >> burst;
    cout << "    Priority => ";
    cin >> priority;
    cout << endl;
    
    ostringstream oss;
    oss << i+1;
    string name = "p" + oss.str();
    processes.push_back(Process(name,arrival,burst,priority));
  }
  displayProcess(processes);
}

void swapProcess(Process& a, Process& b)
{
  Process temp;
  
  temp = a;
  a = b;
  b = temp;
}

void sortProcess(vector<Process>& processes)
{
 // vector<Process> temp = processes;
  sort(processes.begin(), processes.end());
}

void printGantt(vector<string>& processName, vector<int>& processChangeTime)
{
  for(int i = 0; i < processName.size(); i++) //display box
  {
    cout << "+----";
  }
  cout << "+" << endl;

  for(int i = 0; i < processName.size(); i++) //display process name
  {
    cout << " | " << processName[i];
  }
  cout << " | " << endl << " ";

  for(int i = 0; i < processName.size(); i++) // display box again
  {
    cout << "+----";
  }
  cout << "+" << endl << " ";

  for(int i = 0; i < processChangeTime.size(); i++) //display time
  {
    cout << processChangeTime[i];
    
    if(processChangeTime[i] < 10)
      cout << "    ";
    else
      cout << "   ";
  }
  cout << endl << endl;
}

void calcAverage(vector<Process> processes, int executionTime)
{
  double avgTurnaroundTime = 0;
  double avgWaitingTime = 0; //change to double 
  for(int i = 0;i<processes.size();i++)
  {
    processes[i].calcTurnaroundTime();
    processes[i].calcWaitingTime();
    avgTurnaroundTime = avgTurnaroundTime + processes[i].getTurnaroundTime();
    avgWaitingTime = avgWaitingTime + processes[i].getWaitingTime();
  }
  avgTurnaroundTime = avgTurnaroundTime / processes.size();
  avgWaitingTime = avgWaitingTime / processes.size();
  cout << " Average Turnaround Time = " << avgTurnaroundTime << endl;
  cout << " Average Waiting Time = " << avgWaitingTime << endl;
  cout << " Execution Time = " << executionTime << endl << endl;
  cout << "===================================\n  ";
  system("pause");
  cout << "===================================\n\n";

}

void SRTN(vector<Process> processes) // 1
{
  if(processes.size() == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 
  executingSRTN = true;
  
  vector<Process> SRTN2(processes);
  vector<Process> remainingProcesses(processes);
  vector<Process> ready;
  vector<int> processChangeTime; //for gantt chart output
  vector<string> processName; //for gantt chart output
  
  Process running;
  bool changeProcess = false;
  int totalBurst = 0;
  int executionTime = 0;
  
  for(int i = 0; i < SRTN2.size(); i++)
  {
    totalBurst = totalBurst + SRTN2[i].getBurst();
  }
  int time = 0;
  //for(int time = 0; time < totalBurst; time++)
  while(remainingProcesses.size() != 0)
  {
    //cout << endl << "TIME: " << time << endl;
    
    for(int i = 0; i < SRTN2.size(); i++)
    {
      if(time == SRTN2[i].getArrival() )
      {
        //cout << "[Running] Current " << running.getName() << " remaining time: " << running.getRemaining() << endl;
        //cout << "[New Process " << SRTN2[i].getName() << "] Remaining time: " << SRTN2[i].getBurst() << endl << endl;
        if ( SRTN2[i].getBurst() < running.getRemaining() )
        {
          ready.push_back(running);
          running = SRTN2[i];
          changeProcess = true;
          //cout << running.getName();
        }
        else
        {
          ready.push_back(SRTN2[i]);
        }
        sortProcess(ready);
      }
    }

    //cout << "RUNNING :" <<running.getName() << " " << running.getRemaining() << endl;
    
    if(changeProcess == true) //PROBLEM
    { 
      if(running.getName() != "")
        processName.push_back(running.getName());
      else
        processName.push_back("W ");
      
      processChangeTime.push_back(time);

      //cout << running.getName() << " " << time << endl; //if comment this out, weird thing happens
      
      changeProcess = false;
    }
    if(running.getRemaining() >= 2)
    {
      running.setRemaining(running.getRemaining()-1);
    }
    else if(running.getRemaining() == 1) //if running process dies out
    {
      changeProcess = true;

      for(int i = 0; i < remainingProcesses.size(); i++)
      {
        if(running.getName() == remainingProcesses[i].getName())
        {
          if(remainingProcesses.size() > 1)
            remainingProcesses.erase( remainingProcesses.begin() + i);
          else
          {
            remainingProcesses.pop_back();
            processChangeTime.push_back(time+1);
            changeProcess = false;
            executingSRTN = false;
            executionTime = time+1;
          }
       }
      }

      for(int i = 0; i < SRTN2.size(); i++)
      {
        if(running.getName() == SRTN2[i].getName())
        {
          SRTN2[i].setFinishTime(time+1);
        }
      }
      running = ready[0];
      

      if(ready.size() != 0)
        ready.erase( ready.begin() );
    }
    
    if(ready.size() != 0)
    {
      if(running.getRemaining() > ready[0].getRemaining())
      {
        running = ready[0];
        ready.erase( ready.begin() );
        changeProcess = true;
      }
    }

    time++;
  }
  
  bool x = false;
  
  if(x)
    cout << running.getName();
  
  cout << " Shortest Remaining Time Next (SRTN) scheduling: \n "; //gantt chart
  
  if(processName.size() != 0)
  {
    printGantt(processName,processChangeTime);
    calcAverage(SRTN2,executionTime);
  }
  else
  {
    cout << " No process has been run." << endl << endl;
  }
}

void SJFP(vector<Process> processes) // 2: SJF (Shortest Job First)-based pre-emptive Priority
{
  if(processes.size() == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 

  executingSJFP = true;
  vector<Process> SJFP2(processes);
  vector<Process> remainingProcesses(processes);
  vector<Process> ready;
  vector<int> processChangeTime; //for gantt chart output
  vector<string> processName; //for gantt chart output
  
  Process running;
  bool changeProcess = false;
  int totalBurst = 0;
  int executionTime = 0;
  
  for(int i = 0; i < SJFP2.size(); i++)
  {
    totalBurst = totalBurst + SJFP2[i].getBurst();
  }
  //for(int time = 0; time < totalBurst; time++)
  int time = 0;
  while(remainingProcesses.size() != 0)
  {
    //cout << "TIME: " << time << endl;
    for(int i = 0; i < SJFP2.size(); i++)
    {
      if(time == SJFP2[i].getArrival() )
      {
        // cout << "Arrive: " << SJFP2[i].getName() << endl;
        // cout << "[Running] Current " << running.getName() << " remaining time: " << running.getRemaining() << endl;
        // cout << "[New Process " << SJFP2[i].getName() << "] Remaining time: " << SJFP2[i].getBurst() << endl << endl;
        if ( SJFP2[i].getPriority() < running.getPriority() )
        {
          ready.push_back(running);
          running = SJFP2[i];
          changeProcess = true;

        }
        else if( SJFP2[i].getPriority() == running.getPriority() )
        {
          if ( SJFP2[i].getBurst() < running.getRemaining() )
          {
            ready.push_back(running);
            running = SJFP2[i];
            changeProcess = true;
            //cout << running.getName();
          }
          else if ( SJFP2[i].getBurst() == running.getRemaining() )
          {
            ready.push_back(SJFP2[i]);
          }
        }
        else
        {
          ready.push_back(SJFP2[i]);
        }
        sortProcess(ready); //potential bug
      }      
    }
    
    if(changeProcess == true) //PROBLEM
    {
      if(running.getName() != "")
        processName.push_back(running.getName());
      else
        processName.push_back("W ");
        
      processChangeTime.push_back(time);

      //cout << "CHANGE: " << running.getName() << " " << running.getPriority() << " " << running.getRemaining() << endl; //if comment this out, weird thing happens
      
      changeProcess = false;
    }
    if(running.getRemaining() >= 2)
    {
      running.setRemaining(running.getRemaining()-1);
    }
    else if(running.getRemaining() == 1)
    {
      changeProcess = true;

      for(int i = 0; i < remainingProcesses.size(); i++)
      {
        if(running.getName() == remainingProcesses[i].getName())
        {
          if(remainingProcesses.size() > 1)
            remainingProcesses.erase( remainingProcesses.begin() + i);
          else
          {
            remainingProcesses.pop_back();
            
            processChangeTime.push_back(time+1);
            executionTime = time+1;
            changeProcess = false;
            executingSJFP = false;
          }
       }
      }
      
      for(int i = 0; i < SJFP2.size(); i++)
      {
        if(running.getName() == SJFP2[i].getName())
        {
          SJFP2[i].setFinishTime(time+1);
        }
      }
      
      running = ready[0];
      if(ready.size() != 0)
        ready.erase( ready.begin() );
    }
    
    if(ready.size() != 0)
    {
      if(running.getPriority() > ready[0].getPriority()) //pre empt if priority larger than ready queue
      {
        if(running.getRemaining() > ready[0].getRemaining())
        {
          running = ready[0];
          ready.erase( ready.begin() );
          changeProcess = true;
        }
      }
    }   
    time++;
    //cout << "CHANGE: " << running.getName() << " " << running.getPriority() << " " << running.getRemaining() << endl; 

  }
  
  cout << " Shortest Job First-based Priority (SJFP) scheduling: \n "; //gantt chart
  if(processName.size() != 0)
  {
    printGantt(processName,processChangeTime);
    calcAverage(SJFP2,executionTime);
  }
  else
  {
    cout << " No process has been run." << endl << endl;
  }
}

void TQS(vector<Process> processes) //3
{
  if(processes.size() == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 
  
  int cutoff = 5;
  cout << " Enter the cut-off point => ";
  cin >> cutoff;
  
  int timeQuantum;
  cout << " Enter time quantum for the first queue (RR) => ";
  cin >> timeQuantum;
  cout << endl;
  
  executingTQS = true;
  vector<Process> TQS2(processes);
  vector<Process> TQS3;
  vector<Process> remainingProcesses(processes);
  vector<Process> remain_1st;
  vector<Process> remain_2nd;
  vector<Process> TQS_1st;
  vector<Process> TQS_2nd;
  vector<Process> ready;
  vector<Process> ready2;
  vector<int> processChangeTime1; //for gantt chart output
  vector<string> processName1; //for gantt chart output
  vector<int> processChangeTime2; //for gantt chart output
  vector<string> processName2; //for gantt chart output
  
  Process running;
 // Process running2;
  running.setRR(-1);
  bool changeProcess = false;
  bool waiting = false;
  //int totalBurst = 0;
  bool switchQueue = false;
  for(int i = 0; i < TQS2.size(); i++)
  {
    //totalBurst = totalBurst + TQS2[i].getBurst();
    if(TQS2[i].getPriority() <= cutoff)
    {
      //TQS_1st.push_back(TQS2[i]);
     // TQS_1st[i].setRR(timeQuantum);
      TQS2[i].setQueue(1);
      remain_1st.push_back(TQS2[i]);
      TQS2[i].setRR(timeQuantum);
    }
    else
    {
     // TQS_2nd.push_back(TQS2[i]);
     remain_2nd.push_back(TQS2[i]);
      TQS2[i].setQueue(2);
    }
  }
  sortProcess(TQS2);
  //sortProcess(TQS_1st);

  
  int executionTime = 0;
  int time = 0;
  bool entered =false;
  while(remainingProcesses.size() != 0)
  {
    for(int i = 0; i < TQS2.size(); i++)
    {
      if(time == TQS2[i].getArrival())
      {
        if(TQS2[i].getQueue() == 1)
        {
          ready.push_back(TQS2[i]);
          TQS_1st.push_back(TQS2[i]);
        }
        else
        {
          ready2.push_back(TQS2[i]);
          TQS_2nd.push_back(TQS2[i]);
        }
      }
    }
      
      if(TQS_1st.size() != 0)
      {
        //run first queue
        if(running.getRR() == -1)
        {
          running = ready[0];
          changeProcess = true;
          if(ready.size() != 0)
            ready.erase( ready.begin() );
        }
        else if (running.getRR() == 0)
        {
          //cout << "RR"<<endl;
          if(running.getRemaining() >= 1)
          {
            running.setRR(timeQuantum);          
            ready.push_back(running); //put running process into ready queue
            
            running = ready[0]; //put 1st (next) process in the ready queue into running state
            if(ready.size() != 0)
              ready.erase( ready.begin() );
            changeProcess = true; 
          }
          
        }
        
        if(changeProcess == true)
        {
          //cout << running.getName() << " " << running.getRemaining() << endl;
          processName1.push_back(running.getName());
          processChangeTime1.push_back(time);
    
          changeProcess = false;
        }
        
        if(running.getRemaining() >= 1)
        {
          running.setRemaining(running.getRemaining()-1);
          running.setRR(running.getRR()-1);
        }
        
        if(running.getRemaining() == 0)
        {
         // cout << "HEY" << running.getName() << " " << running.getRemaining() << endl;
          changeProcess = true;
  
          for(int i = 0; i < remainingProcesses.size(); i++)
          {
            if(running.getName() == remainingProcesses[i].getName())
            {
              if(remainingProcesses.size() > 1)
                remainingProcesses.erase( remainingProcesses.begin() + i);
              else
              {
                remainingProcesses.pop_back();
                processChangeTime1.push_back(time+1);
                executionTime = time+1;
                changeProcess = false;
              }
           }
          }
          
          for(int i = 0; i < remain_1st.size(); i++)
          {
            if(running.getName() == remain_1st[i].getName())
            {
              if( remain_1st.size() > 1)
                 remain_1st.erase(  remain_1st.begin() + i);
              else
              {
                 remain_1st.pop_back();
              }
            }          
          }
          
          for(int i = 0; i < TQS2.size(); i++)
          {
            if(running.getName() == TQS2[i].getName())
            {
              TQS2[i].setFinishTime(time+1);
            }
          }
          
          if(ready.size() != 0)
            ready.erase( ready.begin() );
            
          for(int i = 0; i < TQS_1st.size(); i++)
          {
            if(running.getName() == TQS_1st[i].getName())
            {
              TQS_1st.erase(TQS_1st.begin()+i);
            }  
          }
          
          if(TQS_1st.size() == 0)
          {
            running.setRR(-1);
            if(TQS_2nd.size() != 0)
            {
              if (TQS_2nd[0].getQueue() == 2)
              {
                processChangeTime1.push_back(time+1);
                switchQueue = true;
              }
            }
            else
            {
              //processChangeTime1.push_back(time+1);//prob
            }
          }
          else
          {
            running = ready[0];
          }
          
          if(TQS_1st.size() == 0 && ready2.size() == 0 && TQS_2nd.size() != 0)
          {
            processChangeTime1.push_back(time+1);
          }
          else if(TQS_1st.size() == 0 && ready2.size() == 0 && remain_2nd.size() != 0)
          {
            processChangeTime1.push_back(time+1);
          }
          

        }
      }
      else if (TQS_1st.size() == 0)
      {
        if(ready2.size() != 0)
        {
          if(switchQueue && remain_1st.size() != 0)
          {
              processName1.push_back("W ");
              switchQueue =false;
          } 
          
          if(running.getRR() == -1)
          {
           
            running = ready2[0];
            running.setRR(-2);
          //  cout << "RUNNING: " << running.getName() << " " << running.getRemaining() << endl;
            changeProcess = true; 
          }
          
           if(changeProcess == true)
          {
            //cout << running.getName() << " " << running.getRemaining() << endl;
            processName2.push_back(running.getName());
            processChangeTime2.push_back(time);
            changeProcess = false;
          }
          if(running.getRemaining() >= 1)
          {
            running.setRemaining(running.getRemaining()-1);
          }
          if(running.getRemaining() == 0)
          {
            changeProcess = true;
            
            for(int i = 0; i < remainingProcesses.size(); i++)
            {
              if(running.getName() == remainingProcesses[i].getName())
              {
                if(remainingProcesses.size() > 1)
                  remainingProcesses.erase( remainingProcesses.begin() + i);
                else
                {
                  remainingProcesses.pop_back();
                  processChangeTime2.push_back(time+1);
                  executionTime = time+1;
                  changeProcess = false;
                  executingSJFP = false;
                }
              }
            }
            
            for(int i = 0; i < TQS2.size(); i++)
            {
              if(running.getName() == TQS2[i].getName())
              {
                TQS2[i].setFinishTime(time+1);
              }
            }
            
            for(int i = 0; i < remain_2nd.size(); i++)
            {
              if(running.getName() == remain_2nd[i].getName())
              {
                if( remain_2nd.size() > 1)
                   remain_2nd.erase(  remain_2nd.begin() + i);
                else
                {
                   remain_2nd.pop_back();
                }
              }          
            }
            
            for(int i = 0; i < TQS_2nd.size(); i++)
            {
              if(running.getName() == TQS_2nd[i].getName())
              {
                TQS_2nd.erase(TQS_2nd.begin()+i);
              }  
            }
            
            
            if(ready2.size() != 0)
              ready2.erase( ready2.begin() );
              running = ready2[0];
          }
          
          if(TQS_1st.size() != 0)
          {
            ready2.push_back(running);
            running = ready[0];
            running.setRR(-1);
            changeProcess = true;
            
          }
          
          for(int i = 0; i < TQS2.size(); i++)
          {
            if(time+1 == TQS2[i].getArrival())
            {
              if(TQS2[i].getQueue() == 1)
              {
                if(ready2.size() != 0)
                  ready2.erase( ready2.begin() );
                  
                 ready2.push_back(running);
                running.setRR(-1);
                processName2.push_back("W ");
                processChangeTime2.push_back(time+1);
              }
            }
          }
          
          if(remain_2nd.size() == 0 && TQS_1st.size() == 0 && remain_1st.size() != 0)
          {
            processChangeTime2.push_back(time+1);
          }
        }
        else
        {
        
        }
      }
    
    time++;

    //cout << "Current running : " << running.getName() << " " << running.getRemaining() << " RR:" << running.getRR() << endl;
    
  }
  
  cout << " Two-level Queue Scheduling:\n";
  cout << " First queue (RR): \n";
  
  if(processName1.size() != 0)
    printGantt(processName1,processChangeTime1);
  else
    cout << " No process has been run in the first queue." << endl << endl;
    
  cout << " Second queue (FCFS): \n";
  if(processName2.size() != 0)
    printGantt(processName2,processChangeTime2);
  else
    cout << " No process has been run in the second queue." << endl;
    
  calcAverage(TQS2,executionTime);
}

void LS(vector<Process> processes) //4
{
  if(processes.size() == 0)
  {
    cout << " No process is found.\n\n";
    system("pause");
    return;
  } 
  vector<Process> LS2(processes);
  vector<Process> remainingProcesses(processes);
  vector<Process> ready;
  vector<int> processChangeTime; //for gantt chart output
  vector<string> processName; //for gantt chart output
  bool done =false;
  bool enterWait = false;
  bool waitDone = false;
  Process running;
  running.setRemaining(-1);
  bool changeProcess = false;
  int totalBurst = 0;
  
  executingSJFP = true; //sort by priority (from high to low)
  sortProcess(LS2);
  executingSJFP = false;
  executingLS = true;
  
  //Process wait(0,0,0);
  vector<int> lottery;
  vector<int> lottery2;// all numbers
  for (int i=1; i<56; ++i)
  {
    lottery.push_back(i);
    lottery2.push_back(i);
  }  
  
  cout << " Distributing lottery ticket randomly...\n\n";
  for(int i = 0; i < LS2.size(); i++)
  {
    int num = LS2.size()-i;
    for(int j = 0; j < num; j++ )
    {
      random_shuffle ( lottery.begin(), lottery.end() );
      LS2[i].setTicket(lottery[0]);
      cout << " Process " << LS2[i].getName() << " got ticket no." << lottery[0] << endl;
      lottery.erase( lottery.begin());
    }
    cout << endl;
  }
  
  bool Done;

  int placed = 0; //as a counter of the number of Processes being placed to allocate cpu
  
  bool check[LS2.size()];
  for(int i = 0; i < LS2.size(); i++)
  {
    check[i] =false;
  }
  int hit = 0;
  bool create = false;
  int executionTime = 0;
  int time = 0;

  while(remainingProcesses.size() != 0)
  {
   // cout << "TIME: " << time << endl;
    int num = 0;
    for(int i = 0; i < LS2.size(); i++)
    {
      if(LS2[i].getArrival() == time)
      {
        ready.push_back(LS2[i]);
      } 
    }

    if(running.getRemaining() <= 0  )
    {
      for(int i = 0; i < remainingProcesses.size(); i++)
      {
        if(running.getName() == remainingProcesses[i].getName())
        {
          if(remainingProcesses.size() > 1)
            remainingProcesses.erase( remainingProcesses.begin() + i);
          else
          {
            remainingProcesses.pop_back();
            
            processChangeTime.push_back(time);
            changeProcess = false;
            executionTime = time;
            executingLS = false;
          }
       }
      }
      
      for(int i = 0; i < LS2.size(); i++)
      {
        if(running.getName() == LS2[i].getName())
        {
          LS2[i].setFinishTime(time);
        }
      }
      
      if(ready.size() == 0)
      {
        if(!waitDone && remainingProcesses.size() != 0)
        {
          enterWait = true;
        }
      }
       if(ready.size() == 1)
      {
        num=0;
        running = ready[0];
        changeProcess = true;
      }
      else if(ready.size() > 1)
      {
        if(placed < LS2.size()-1)
        {
          done = false;
          while(!done)
          {
            cout << " Drawing Lot... \n";
            if(lottery2.size() != 0)
            random_shuffle ( lottery2.begin(), lottery2.end() );
              cout << " Chosen Lottery Ticket Number: " << lottery2[0] << "\n";
              
            for(int i = 0; i < ready.size(); i++)
            {
              //cout << "i: " << i << "    name: " << ready[i].getName() << endl;
              for(int j = 0; j < ready[i].getTicket().size(); j++)
              {
                if (ready[i].getTicket()[j] == lottery2[0])
                {
                  cout << " " << lottery2[0] << " is being held by Process " << ready[i].getName() << "!\n";
                  running = ready[i];
                  num = i;
                        
                  changeProcess = true; 
                  check[i] = true;
                  cout << " Process " << ready[i].getName() << " is now allocated to access CPU resources. \n";
                }
              }

            }
            cout << endl;
            if(lottery2.size() != 0)
            {
              lottery2.erase(lottery2.begin());
            }
            
            if(changeProcess)
              done = true;
          }
        }
        else
        {
          changeProcess= true;
          
          for(int x = 0; x < LS2.size(); x++)
          {
            if(check[x] == false)
              running = ready[x];
          }
        }
      }
    }
    if(running.getRemaining() > 0)
    {
      running.setRemaining(running.getRemaining()-1);
    }
    if (enterWait)
    {
      processName.push_back("W ");
      processChangeTime.push_back(time);
      waitDone = true;
      enterWait = false;
    }

    if(changeProcess)
    {
      if(running.getName() != "")
        processName.push_back(running.getName());
      else
        processName.push_back("W ");
      
      if(ready.size() != 0) //bug
        ready.erase( ready.begin()+num );

      processChangeTime.push_back(time);

      //cout << running.getName() << " " << time << endl; //if comment this out, weird thing happens
      placed = placed+1;

      changeProcess = false;
    }
      done = false;
      time++;
     // cout << running.getName() << " " << running.getRemaining() << endl;
  }
  cout << " Lottery scheduling: \n "; //gantt chart

  if(processName.size() != 0)
  {
    printGantt(processName,processChangeTime);
    calcAverage(LS2,executionTime);
  }
  else
  {
    cout << " No process has been run." << endl << endl;
  }
  
  executingLS = false;
  
}

void editProcess(vector<Process>& processes)
{
  displayProcess(processes);
  
  if(processes.size() == 0)
    return;
    
  bool found = false;
  string name;
  cout << " The name of the process that is to be modified? => ";
  cin >> name;
  
  int ans;
  
  for(int i = 0; i < processes.size(); i++)
  {
    if(name == processes[i].getName())
    {
      found = true;
      cout << "   Arrival Time => ";
      cin >> ans;
      processes[i].setArrival(ans);
      
      cout << "   Burst Time => ";
      cin >> ans;
      processes[i].setBurst(ans);
      
      cout << "   Priority => ";
      cin >> ans;
      processes[i].setPriority(ans);
      
      cout << "\nThe process has successfully been modified.\n\n";
    }
  }
 
  if(!found)
    cout << "Process with name " << name << " could not be found.\n\n";
  
  system("pause");
}

void addProcess(vector<Process>& processes)
{
  displayProcess(processes);
  
  if(processes.size() == 0)
    return;
  Process newProcess;
  string name;
  int ans;

  cout << " New process name => ";  
  cin >> name;
  for(int i = 0; i < processes.size(); i++)
  {
    if(name == processes[i].getName())
    {
      cout << " The name " << name << " is already in use. Please choose another name.\n";
      system("pause");
      return;
    }
  }
  newProcess.setName(name);
  
  cout << "   Arrival Time => ";
  cin >> ans;
  newProcess.setArrival(ans);

  cout << "   Burst Time => ";
  cin >> ans;
  newProcess.setBurst(ans);

  cout << "   Priority => ";
  cin >> ans;
  newProcess.setPriority(ans);
  
  processes.push_back(newProcess);
  cout << " New process with name " << name << " has successfully been created.\n\n";
  system("pause");
}

void deleteProcess(vector<Process>& processes)
{
  displayProcess(processes);
  if(processes.size() == 0)
    return;
    
  bool found = false;
  string name;
  cout << "Enter the name of the process that will be deleted => ";
  cin >> name;
  
  for(int i = 0; i < processes.size(); i++)
  {
    if(name == processes[i].getName())
    {
      found = true;
      processes.erase(processes.begin()+i);
      cout << "Process with name " << name << " has successfully been deleted.\n\n";
    }
  }
 
  if(!found)
    cout << "Process with name " << name << " could not be found.\n\n";
  
  system("pause");  
}

void mainMenu()
{
  vector<Process> processes;
  
  int choice = 0;
  while(choice != 11) //exit
  {
    system("cls");
    cout << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " | Main Menu                                                 |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " | Processes:                                                |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " |   1. Initialize processes                                 |" << endl;
    cout << " |   2. Display current processes                            |" << endl;
    cout << " |   3. Modify a process                                     |" << endl;
    cout << " |   4. Add a process                                        |" << endl;
    cout << " |   5. Delete a process                                     |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " | Scheduling:                                               |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " |   6. Shortest Remaining Time Next (SRTN)                  |" << endl;
    cout << " |   7. Shortest Job First-based pre-emptive Priority (SJFP) |" << endl;
    cout << " |   8. Two-level Queue Scheduling                           |" << endl;
    cout << " |   9. Lottery Scheduling                                   |" << endl;
    cout << " |   10. All                                                 |" << endl;
    cout << " +-----------------------------------------------------------+" << endl;
    cout << " |   11. Exit                                                |" << endl;
    cout << " +-----------------------------------------------------------+" << endl << endl;
  

    cout << " Your selection => ";
    cin >> choice;
    
    switch(choice)
    {
      case 1:
      initialize(processes);
      break;
      
      case 2:
      displayProcess(processes);
      break;
      
      case 3:
      editProcess(processes);
      break;
      
      case 4:
      addProcess(processes);
      break;
      
      case 5:
      deleteProcess(processes);
      break;
      
      case 6:
      SRTN(processes);
      break;
      
      case 7:
      SJFP(processes);
      break;
      
      case 8:
      TQS(processes);
      break;
      
      case 9:
      LS(processes);
      break;
      
      case 10:
      if(processes.size() == 0)
      {
        cout << " No process is found.\n";
        system("pause");
      }
      else
      {
        SRTN(processes);
        SJFP(processes);
        TQS(processes);
        LS(processes);      
      }
      break;
      
      case 11:
      cout << " Successfully exited the program. \n";
      break;
    }
  }
}

void setWindow(int Width, int Height)
{
  _COORD coord;
  coord.X = Width;
  coord.Y = Height;

  _SMALL_RECT Rect;
  Rect.Top = 0;
  Rect.Left = 0;
  Rect.Bottom = Height - 1;
  Rect.Right = Width - 1;

  HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
  SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
  SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

int main()
{
  srand(time(0));
  setWindow(200,200);
  mainMenu();
  return 0;
}