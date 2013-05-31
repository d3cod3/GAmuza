/*
    ofxHttpUtils v0.3
    Chris O'Shea, Arturo, Jesus, CJ

    Modified: 16th March 2009
    openFrameworks 0.06

*/
#ifndef OFX_HTTP_TYPES
#define OFX_HTTP_TYPES


#define OFX_HTTP_GET  0
#define OFX_HTTP_POST 1

struct ofxHttpForm{


	int method;
	string action;
	string name;

    ofxHttpForm(){
    	method = OFX_HTTP_GET;
    	expectBinaryResponse = false;
    }
    ~ofxHttpForm(){
        clearFormFields();
    }

	// ----------------------------------------------------------------------
	void addFormField(string id, string value){
        formIds.push_back( id );
        formValues.push_back( value );
	}
	// ----------------------------------------------------------------------
	void clearFormFields(){
	    formIds.clear();
        formValues.clear();
        formFiles.clear();
	}
	// ----------------------------------------------------------------------
	void addFile(string fieldName, string path){
		formFiles[fieldName] = ofToDataPath(path);
	}

	string getFieldValue(string id){
		for(unsigned int i=0;i<formIds.size();i++){
			if(formIds[i]==id) return formValues[i];
		}
		return "";
	}

	vector <string> formIds;
	vector <string> formValues;
	std::map<string,string> formFiles;
	bool expectBinaryResponse;
};

#endif
