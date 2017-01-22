package github

func CreateIssue(title, body string, assignees []*IssueCreateAssignee, terms []string) *IssueCreateResponse {
	q := terms[0] //url.QueryEscape(strings.Join(terms, " "))

	var reqBody IssueCreateRequest
	reqBody.Title = title
	reqBody.Body = body
	reqBody.Assignees = assignees

	reqBodyData, err := json.Marshal(reqBody)
	if err != nil {
		log.Println("Could not Marshal IssueCreateRequest")
		return nil
	}
	fmt.Println("Result JSON to request: ", string(reqBodyData))
	createURL := CreateIssueURL + "" + q
	fmt.Println("Query URL: ", createURL)
	req, err := http.NewRequest("POST", createURL, bytes.NewBuffer(reqBodyData))
	if err != nil {
		log.Println("Could not create HTTP Resquest: ", err)
		return nil
	}

	req.Header.Set("X-Custom-Header", "createIssue")
	req.Header.Set("Content-Type", "application/json")

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Printf("Github Username: ")
	scanner.Scan()
	userLogin := scanner.Text()
	fmt.Println("")
	fmt.Printf("Github password (for simplicity echo will on) :")
	scanner.Scan()
	userPassword := scanner.Text()

	req.SetBasicAuth(userLogin, userPassword)
	client := &http.Client{}
	resp, err := client.Do(req)

	if err != nil {
		log.Println("Coult not execute Post :", err)
		return nil
	}
	bodyData, _ := ioutil.ReadAll(resp.Body)

	defer resp.Body.Close()

	respCreateIssue := new(IssueCreateResponse)
	e := json.Unmarshal(bodyData, respCreateIssue)
	if e != nil {
		log.Println("Could not parse create issue response")
		return nil
	}
	fmt.Println("Query Result (raw body data) ", string(bodyData))
	return respCreateIssue

}
