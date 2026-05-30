#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct HttpStatus {
    int code;
    string message;

    static const HttpStatus OK;
    static const HttpStatus BAD_REQUEST;
    static const HttpStatus NOT_FOUND;
    static const HttpStatus INTERNAL_SERVER_ERROR;

    bool isSuccess() const {
        // Return true if code < 400
        return code < 400;
    }

    void display() const {
        // Print: "CODE MESSAGE" e.g. "200 OK"
        cout<<code<<" "<<message<<endl;
    }

    /*
    - The values() function returns a static vector of pointers to predefined HttpStatus objects (like OK, NOT_FOUND), ensuring the vector is created only once.
    - Returning the vector by const reference avoids copying it each time the function is called, which is more efficient.
    - Returning the vector by value (without the reference) would create a copy each time, which works but is less performant.
    - Returning a pointer to the vector itself (i.e., return &v) would be unsafe because you’d be giving raw access to the vector’s internal memory, which is not the intent.
    - The reference returned is const, so it allows read-only access to the vector—no one can modify it.
    - This setup ensures safe, efficient access to the predefined statuses without unnecessary duplication or unsafe pointer exposure.
    */

    static const HttpStatus* fromCode(int code) {
        // Return pointer to HttpStatus matching the code, or nullptr if not found
        for (const HttpStatus* status : values())
            if (status->code == code) return status;
        return nullptr;
    }

    static const vector<const HttpStatus*>& values() {
        static vector<const HttpStatus*> v = {&OK, &BAD_REQUEST, &NOT_FOUND, &INTERNAL_SERVER_ERROR};
        return v;
    }
};

// Set correct values: OK(200, "OK"), BAD_REQUEST(400, "Bad Request"),
// NOT_FOUND(404, "Not Found"), INTERNAL_SERVER_ERROR(500, "Internal Server Error")
const HttpStatus HttpStatus::OK{200, "OK"};
const HttpStatus HttpStatus::BAD_REQUEST{400, "Bad Request"};
const HttpStatus HttpStatus::NOT_FOUND{404, "Not Found"};
const HttpStatus HttpStatus::INTERNAL_SERVER_ERROR{500, "Internal Server Error"};

int main() {
    HttpStatus::OK.display();
    HttpStatus::NOT_FOUND.display();

    cout << "Is 200 success? " << (HttpStatus::OK.isSuccess() ? "true" : "false") << endl;
    cout << "Is 404 success? " << (HttpStatus::NOT_FOUND.isSuccess() ? "true" : "false") << endl;

    const HttpStatus* found = HttpStatus::fromCode(500);
    if (found != nullptr) {
        cout << "Found by code 500: ";
        found->display();
    }
    return 0;
}