#include<iostream>
#include<memory>
#include<string>

class MessageProcessor{		
};

class Message{
public:

	Message(std::shared_ptr<MessageProcessor>  _msg_proc, int _id){
		proc_weak = std::weak_ptr<MessageProcessor>(_msg_proc);
		proc_shared = _msg_proc;
		id = _id;
	}

	std::weak_ptr<MessageProcessor> proc_weak;
	std::shared_ptr<MessageProcessor> proc_shared;	
	int id;
};

int main(){
	
	std::shared_ptr<MessageProcessor> proc(new MessageProcessor());
	
	Message msg(proc,1);
	
	
	if( !msg.proc_weak.expired() )
		std::cout << "1) proc_weak is not EXPIRED. As expected" << std::endl;
	
	if( msg.proc_shared != nullptr )
		std::cout << "2) proc_shared is not EXPIRED. As expected" << std::endl;
	
	msg.proc_shared = std::shared_ptr<MessageProcessor>();	
	// there is still the 'proc' reference	
	if( !msg.proc_weak.expired() )
		std::cout << "3) proc_weak has not EXPIRED yet. As expected" << std::endl;
	proc = std::shared_ptr<MessageProcessor>();
	// There is no more refs in shared_pointer!
	if( msg.proc_weak.expired() )
		std::cout << "4) proc_weak has EXPIRED. As expected" << std::endl;
	
	return 0; 
}
