#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

/**
 Some examples using templates functions from <algorithm>
 @author Wesley Mesquita
 @email wesleymesquita@gmail.com
 */

class Mail{
public:
    Mail(const std::string& message_, const std::string& from, const std::string& to);
    bool operator ==(const Mail& rhs) const;
    const std::string& getFrom() const;
private:
    std::string message;
    std::string from;
    std::string to;
};

Mail::Mail(const std::string& message_, const std::string& from_, const std::string& to_): 
message(message_), 
from(from_),
to(to_)
{            
}

bool Mail::operator ==(const Mail& rhs) const{
    return from.compare(rhs.from) == 0 &&
            to.compare(rhs.to) == 0 &&
            message.compare(rhs.message) == 0;
}

const std::string& Mail::getFrom() const
{
   return this->from;
}


int main()
{
    
    
    std::vector<std::string> emails = {"a@b.com", "c@b.com", "d@b.com", "a@h.com"};
    
    // std::all_of
    {
    std::string prefix = "b.com";
    bool is_all_same_prefix = std::all_of(emails.begin(), 
            emails.end(), 
            [&](std::string email){return email.find(prefix) != std::string::npos;} );
    std::cout << "all_of " << is_all_same_prefix << std::endl;
    }
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
    
    std::vector<Mail> mail_list = {{"BLA", "a@b.com", "c@d.com"}, {"BLA", "a@b.com", "c@d.com"}, {"BLZ", "a@c.com", "b@c.com"}};
    
    // std::count 
    size_t count_mail = std::count(mail_list.begin(), mail_list.end(), Mail("BLA", "a@b.com", "c@d.com"));
    std::cout << "Found " << count_mail << " mails" << std::endl;
    
    //std::count_if
    size_t count_mail_if = std::count_if(mail_list.begin(), mail_list.end(), [&](Mail& mail){return mail.getFrom().compare("a@b.com") == 0;});    
    std::cout << "Found " << count_mail_if << " mails where 'from' == a@b.com" << std::endl;
 
    //std::mismatch
    std::string A = "ORIGINAL MESSAGE";
    std::string B = "ORIGINAL MEMESSAGE";    
    auto it_pair = std::mismatch(A.begin(), A.end(), B.begin());
    std::cout << "@A dif starts at " << it_pair.first - A.begin() << " and @ B starts in " << it_pair.second - B.begin() << std::endl; 

    //std::equal
    std::vector<Mail> mail_list2 = {{"BLA", "a@b.com", "c@d.com"}, {"BLA", "a@b.com", "c@d.com"}, {"BLZ", "a@c.com", "b@c.com"}};
    bool equal_lists = std::equal(mail_list.begin(), mail_list.end(), mail_list2.begin());    
    std::cout << "Both lists are " << [&](){return equal_lists ? "equal": "not equal";}() << std::endl;

    //std::is_permutation
    {
        std::string str1 = "ABCDE";
        std::string str2 = "EBCDA";  
        bool perm = std::is_permutation(str1.begin(), str1.end(), str2.begin());
        std::cout << str2 << [&](){return perm ? " is a permutation" : " is not a permutation";}() << " of " << str2 << std::endl;
     
        str1 = "FABCDE";
        str2 = "EBFCDA";  
        perm = std::is_permutation(str1.begin(), str1.end(), str2.begin());
        std::cout << str2 << [&](){return perm ? " is a permutation" : " is not a permutation";}() << " of " << str2 << std::endl;

        str1 = "FABCDEH";
        str2 = "EBFCDA";  
        perm = std::is_permutation(str1.begin(), str1.end(), str2.begin());
        std::cout << str2 << [&](){return perm ? " is a permutation" : " is not a permutation";}() << " of " << str2 << std::endl;
    }
    //std::search    
    {
        std::string all_text = "The hardest thing in the world to understand is the income tax.";
        std::vector<std::string> to_find = {"the", "in", "to","is", "on", "between", "among"};
    
        for(std::string find_str: to_find){
            auto it_ptr = all_text.begin();
            
            do{
              it_ptr = std::search(it_ptr, all_text.end(), find_str.begin(), find_str.end());
              if(it_ptr != all_text.end()){
                std::cout << "Found " << find_str << " @ " << all_text << "[" << (it_ptr - all_text.begin())  << "]" << std::endl;              
                it_ptr++;
              }          
            }while(it_ptr != all_text.end());
         }    
    }
        
    //std::search_n
    {
         std::string str1 = "ABAABAAABAAAABAAAAAB";
         const char elem = 'A';
         for(int n=1;; n++){
          auto it = std::search_n(str1.begin(), str1.end(),n, elem);
          if( it != str1.end() ){
              std::cout << "Found " ;               
              [=](int n_, char elem_){while(n_--) { std::cout << elem_; } }(n, elem);
              std::cout << " @ pos " << ( it - str1.begin() ) << std::endl;
          }      
          else{
              break;
          }
       }
    }

    {
       //std::copy    
        const std::string line = "From: \"Bob Example\" <bob@example.org>";
       size_t pos_ini = line.find("<");
       size_t pos_end = line.find(">");
       std::vector<char> extracted_email;
       if(pos_ini == std::string::npos || pos_end == std::string::npos){
           std::cerr << "Email address not found " << std::endl;
       }
       else{
           extracted_email.resize(pos_end - pos_ini, '\0');
           std::copy(line.begin() + pos_ini + 1, line.begin() + pos_end, extracted_email.begin() );                     
           std::cout << "extracted_email: " 
                   << std::string(extracted_email.data()) 
                   << std::endl;
       }
    }
    
    
    {
       //std::copy_n 
       const std::string line = "bob@example.org";
       size_t pos_ini = line.find("@");
       std::vector<char> extracted_user;
       if( pos_ini == std::string::npos ){
           std::cerr << "Could not extract user" << std::endl;
       }
       else{
           extracted_user.resize(pos_ini, '\0');
           std::copy_n(line.begin(), pos_ini, extracted_user.begin() );                     
           std::cout << "extracted_user: " 
                   << std::string(extracted_user.data()) 
                   << std::endl;
       } 
    }
    
    {
        //std::copy_if
    
        std::vector<Mail> mails_search = {
            {"message1", "a@b.com", "c@d.com"}, 
            {"message2", "a@b.com", "e@d.com"},  
            {"message3", "e@f.com", "a@b.com"},            
        }; 
       
        std::vector<Mail> mails_from_a_at_b_dot_com;
        mails_from_a_at_b_dot_com.reserve(mails_search.size()); 
        
        std::copy_if(mails_search.begin(), mails_search.end(), 
                std::back_inserter(mails_from_a_at_b_dot_com), 
                [&](Mail mail){return mail.getFrom().compare("a@b.com") == 0;});        
        std::cout << "The are " 
                << mails_from_a_at_b_dot_com.size() 
                << " emails from a@b.com" 
                << std::endl;   
    }
    
    {
       //std::copy_backward
       std::vector<int> vec1 = {1,2,3,4,5};
       std::vector<int> vec2;
       vec2.resize(vec1.size());
       std::copy_backward(vec1.begin(), vec1.end(), vec2.end());
       std::for_each(vec2.begin(), vec2.end(),  [](int i){std::cout << i << " - ";} );
       std::cout << std::endl;       
    }    
    {
      //std::move
    std::vector<std::string> email_doms = {".com.br", ".com", ".net.br"};	
    std::vector<std::string> new_email_doms;
    new_email_doms.reserve(email_doms.size());
    std::move(email_doms.begin(), email_doms.end(), new_email_doms.begin());
    
    }
        
    
}
    

