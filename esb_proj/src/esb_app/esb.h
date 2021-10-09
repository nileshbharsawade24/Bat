/*
/ Author : Rohit Kumar Bhamu
/ Designation : Senior Technical Member
/ Employer : Broadridge
*/
#ifndef HEADER_FILE
#define HEADER_FILE
//Structure for BMD Message data
typedef struct {
    char *MessageID;
    char *MessageType;
    char *Sender;
    char *Destination;
    char *CreationDateTime;
    char *Signature;
    char *ReferenceID;
}bmd_envelop;

typedef struct {
    bmd_envelop envelop;
    char* payload;
}bmd;

#endif
// typedef struct {
//     char* sender;
//     char* destination;
//     char* message_type;
//     char* message_id;
//     char* signature;
//     char* reference_id;
//     char* create_on;
// } bmd_envelop;
