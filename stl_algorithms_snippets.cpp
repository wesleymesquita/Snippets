#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

int main()
{
    std::vector<std::string> emails = {"a@b.com", "c@b.com", "d@b.com", "a@h.com"};
    
    // std::all_of
    std::string prefix = "b.com";
    bool is_all_same_prefix = std::all_of(emails.begin(), 
            emails.end(), 
            [&](std::string email){return email.find(prefix) != std::string::npos;} );
    std::cout << "all_of " << is_all_same_prefix << std::endl;

    // std::any_of
    std::string prefix2 = "h.com";    
    bool has_at_least_one = std::any_of(emails.begin(), 
            emails.end(), 
            [&](std::string email){ return email.find(prefix2) != std::string::npos;});
    std::cout << "any_of " << has_at_least_one << std::endl;
    
    // std::none_of
    std::string prefix3 = "g.com";    
    bool none_of = std::none_of(emails.begin(), 
            emails.end(), 
            [&](std::string email){ return email.find(prefix3) != std::string::npos;});
    std::cout << "none_of: " << [&](){return none_of?"true":"false";}() << std::endl;
   
    // std::for_each    
    std::for_each(emails.begin(), 
            emails.end(), 
            [](std::string email){ std::cout << email << std::endl; } );

    // std::find
    if( std::find(emails.begin(), emails.end(), std::string("a@b.com")) != emails.end()  ){
        std::cout << "found " << "a@b.com" << std::endl;
    }    
     
    // std::find_if
    if( std::find_if(emails.begin(), 
            emails.end(), 
            [&](std::string mail){ return mail.compare( std::string("a@b.com")) == 0; } ) != emails.end() ) {
        std::cout << "found_if  " << "a@b.com" << std::endl;
    }    
   
    // std::find_if_not    
    if( std::find_if_not(emails.begin(), 
            emails.end(), 
            [&](std::string mail){ return mail.compare( std::string("a@govno.com")) == 0; } ) != emails.end() ) {
        std::cout << "found_if_not  " << "a@govno.com" << std::endl;
    }        

    // std::find_end
    std::string gov_prefix = "@gov.br";
    std::string mail = "someone@gov.br";
    auto it = std::find_end(mail.begin(), mail.end(), gov_prefix.begin(), gov_prefix.end());
    if(it != mail.end()){
        std::cout << gov_prefix << " found @ pos:" << (it - mail.begin()); 
    }
    
    // std::find_first_of
    std::string user = "someone";
    std::string someone_mail = "someone_someone@gov.br";
    auto it2 = std::find_first_of(someone_mail.begin(), 
            someone_mail.end(), 
            user.begin(), 
            user.end(),
            [&](char c_mail, char c_user){return c_mail == c_user;} );
    if(it2 != mail.end()){
        std::cout << user << " found @ pos:" << (it2 - someone_mail.begin()) << std::endl; 
    }
    
    // std::adjacent_find
    std::cout << std::endl;
    std::string base_str = "ABCDEFFFGHHHIJJ";         
    int i = 0;
    auto base_str_it = base_str.begin(); 
    for(;;){
        auto it_ = std::adjacent_find(base_str_it, base_str.end());
        if(it_ != base_str.end()){
            std::cout << "Consecutive " << *it_ << " @ " << ( it_ - base_str.begin() ) << std::endl;   
            base_str_it = it_+1;
        }
        else
        {
           break;
        }
    }    
    
    

}       

