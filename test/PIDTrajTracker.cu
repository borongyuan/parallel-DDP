/***
nvcc -std=c++11 -o PID.exe PIDTrajTracker.cu ../utils/cudaUtils.cu ../utils/threadUtils.cpp -llcm -gencode arch=compute_61,code=sm_61 -rdc=true -O3
***/
#define USE_WAFR_URDF 0
#define EE_COST 1
#define USE_LIMITS_FLAG 0
#define MPC_MODE 1
#define USE_EE_VEL_COST 0
#define USE_LCM 1
#define USE_VELOCITY_FILTER 0
#define PLANT 4
#define HARDWARE_MODE 0
#include <iostream>
#include "../config.cuh"

/**********
f = open('t.txt','r')
data = f.readlines()
out = 'double qData[] = {'
o_data = []
for row in data:
    stamp, rest = row.split(']')
    q,qd,u = rest.split('|')
    qs = q.split(' ')
    r_qs = qs[1:-1]
    o_data += r_qs
out += ','.join(o_data)
out += '};'
f = open('t2.txt','w')
f.write(out)
print len(o_data)/7
***********/


class LCM_PIDTracker_Handler {
    public:
        lcm::LCM lcm_ptr;   bool running;
        LCM_PIDTracker_Handler(){running = 0;    if(!lcm_ptr.good()){printf("LCM Failed to Init in PIDTracker\n");}}
        ~LCM_PIDTracker_Handler(){}

        // lcm callback function to update the initial t0
        void handleMessage(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const drake::lcmt_iiwa_status *msg){
            if(!running){running = 1;    runTracker(msg->utime);}
        }

        // do tracking
        void runTracker(int64_t t0){
            struct timeval start, end; gettimeofday(&start,NULL); int counter = 0;
            printf("Tracker running with t0[%ld]\n",t0);
            while(counter < 18044){
                double tk = t0 + counter*1000;    double *qk = &qData[counter*NUM_POS];  counter++;
                #if HARDWARE_MODE
                	drake::lcmt_iiwa_command_hardware dataOut;
                	#pragma unroll
	                for(int i=0; i < 6; i++){dataOut.wrench[i] = 0.0;}
	            #else
	                drake::lcmt_iiwa_command dataOut;   
	                dataOut.num_torques = static_cast<int32_t>(CONTROL_SIZE);
	            #endif
	            dataOut.num_joints = static_cast<int32_t>(NUM_POS);         dataOut.joint_position.resize(dataOut.num_joints);
	            dataOut.utime = tk;           								dataOut.joint_torque.resize(dataOut.num_joints);  // NUM_POS = CONTROL_SIZE for arm so this works
                // zero torques and send positions
                #pragma unroll
                for (int i = 0; i < NUM_POS; i++){dataOut.joint_torque[i] = 0;}
                #pragma unroll
                for (int i = 0; i < NUM_POS; i++){dataOut.joint_position[i] = qk[i];}
                printf("Time[%d][%ld] qk[%f %f %f %f %f %f %f]\n",counter,dataOut.utime,dataOut.joint_position[0],
                                    dataOut.joint_position[1],dataOut.joint_position[2],dataOut.joint_position[3],
                                    dataOut.joint_position[4],dataOut.joint_position[5],dataOut.joint_position[6]);
                lcm_ptr.publish(ARM_COMMAND_CHANNEL,&dataOut);
                // wait for 1 ms
                while(1){gettimeofday(&end,NULL);    if (time_delta_ms(start,end) >= 1.0){gettimeofday(&start,NULL); break;}}
            }
        }
};


__host__
void runPIDTracker(){
    lcm::LCM lcm_ptr;   if(!lcm_ptr.good()){printf("LCM Failed to Init in PIDTracker\n");}
    LCM_PIDTracker_Handler handler = LCM_PIDTracker_Handler();
    lcm::Subscription *sub = lcm_ptr.subscribe(ARM_STATUS_CHANNEL, &LCM_PIDTracker_Handler::handleMessage, &handler);
    sub->setQueueCapacity(1);
    while(0 == lcm_ptr.handle());
}

int main(int argc, char *argv[])
{
    printf("Press enter to begin\n");    std::string input;  getline(std::cin, input);
    runPIDTracker();
}