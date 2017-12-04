/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    private List<String> validList = new ArrayList<>();
    private List<String> invalidList = new ArrayList<>();

    public UrlValidatorTest(String testName) {
        super(testName);
    }


    public void testManualTest() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println(urlVal.isValid("http://www.amazon.com"));
    }

    private void testURL(String url, UrlValidator urlValidator, List<String> valid, List<String> invalid) {
        if (urlValidator.isValid(url)) {
            valid.add(url);
        } else {
            invalid.add(url);
        }
    }

    private void printResults(int validCount, int invalidCount) {
        System.out.println("Expected valid count: " + validCount + ", actual valid count: " + validList.size());
        System.out.println("Expected invalid count: " + invalidCount + ", actual invalid count: " + invalidList.size());

        System.out.print("Valid: ");
        for (String auth : validList) {
            System.out.print(auth + ", ");
        }

        System.out.println();

        System.out.print("Invalid: ");
        for (String auth : invalidList) {
            System.out.print(auth + ", ");
        }

        // clean up lists
        validList.clear();
        invalidList.clear();
    }

    private void printResults() {
        System.out.print("Valid: ");
        for (String auth : validList) {
            System.out.print(auth + ", ");
        }

        System.out.println();

        System.out.print("Invalid: ");
        for (String auth : invalidList) {
            System.out.print(auth + ", ");
        }

        // clean up lists
        validList.clear();
        invalidList.clear();
    }

    public void testSchemePartition() {
        ResultPair[] testSchemes = {
                new ResultPair("http://", true),
                new ResultPair("ftp://", true),
                new ResultPair("h3t://", true),
                new ResultPair("", true),
                new ResultPair("3ht://", false),
                new ResultPair("http:/", false),
                new ResultPair("http:", false),
                new ResultPair("http/", false),
                new ResultPair("://", false)
        };

        final String URL = "www.google.com";
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (int i = 0; i < testSchemes.length; i++) {
            testURL(testSchemes[i].item + URL, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testSchemePartition ==============\n");
        printResults(4, 5);
    }

    public void testAuthorityPartition() {
        ResultPair[] testAuthority = {
                new ResultPair("www.google.com", true),
                new ResultPair("go.com", true),
                new ResultPair("go.au", true),
                new ResultPair("0.0.0.0", true),
                new ResultPair("go.cc", true),
                new ResultPair("255.255.255.255", true),
                new ResultPair("255.com", true),
                new ResultPair("256.256.256.256", false),
                new ResultPair("1.2.3.4.5", false),
                new ResultPair("1.2.3.4.", false),
                new ResultPair("1.2.3", false),
                new ResultPair(".1.2.3.4", false),
                new ResultPair("go.a", false),
                new ResultPair("go.a1a", false),
                new ResultPair("go.1aa", false),
                new ResultPair("aaa.", false),
                new ResultPair(".aaa", false),
                new ResultPair("aaa", false),
                new ResultPair("", false)
        };

        final String SCHEME = "http://";
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (int i = 0; i < testAuthority.length; i++) {
            testURL(SCHEME + testAuthority[i].item, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testAuthorityPartition ==============\n");
        printResults(7, 12);
    }

    public void testPortPartition()
    {
        ResultPair[] testPort = {
                new ResultPair(":80", true),
                new ResultPair(":65535", true),
                new ResultPair(":0", true),
                new ResultPair("", true),
                new ResultPair(":-1", false),
                new ResultPair(":65636", true),
                new ResultPair(":65a", false)
        };

        final String SCHEME = "http://";
        final String URL = "www.google.com";
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (int i = 0; i < testPort.length; i++) {
            testURL(SCHEME + URL + testPort[i].item, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testPortPartition ==============\n");
        printResults(5, 2);
    }

    /*
     *  Research:
     *      https://stackoverflow.com/questions/1547899/which-characters-make-a-url-invalid
     */
    public void testPathPartition() {
        ResultPair[] testPath = {
                new ResultPair("", true),
                new ResultPair("/abc", true),
                new ResultPair("/abc1", true),
                new ResultPair("/abc123", true),
                new ResultPair("/abc-123", true),
                new ResultPair("/abc_123", true),
                new ResultPair("/abc/123", true),
                new ResultPair("/abc/123/def", true),
                new ResultPair("/abc//123", false),
                new ResultPair("/abc//123", false),
                new ResultPair("/abc^123", false),
                new ResultPair("/abc{123", false),
                new ResultPair("/abc}123", false),
                new ResultPair("/abc|123", false),
                new ResultPair("/abc>123", false),
                new ResultPair("/abc<123", false),
        };
        final String SCHEME = "http://";
        final String URL = "www.google.com";
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (ResultPair aTestPath : testPath) {
            testURL(SCHEME + URL + aTestPath.item, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testPathPartition ==============\n");
        printResults(8, 8);
    }

    /*
     *  Research:
     *      https://en.wikipedia.org/wiki/Query_string
     */
    public void testQueryPartition() {
        ResultPair[] testQuery = {
                new ResultPair("", true),
                new ResultPair("?", true),
                new ResultPair("search?abc=123", true),
                new ResultPair("?abc=123", true),
                new ResultPair("?field1=value1", true),
                new ResultPair("?field1=value1&field2=value2", true),
                new ResultPair("page.html?q=1;q=2;q=3", true),
                new ResultPair("?@bar._=???/1:", true),
                new ResultPair("file?id=wjVg/\n", true),
        };
        final String SCHEME = "http://";
        final String URL = "www.google.com/";
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (ResultPair aTestQuery : testQuery) {
            testURL(SCHEME + URL + aTestQuery.item, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testQueryPartition ==============\n");
        printResults(9, 0);
    }

    public void testIsValid() {
        String[] schemeInput = {"http://", "h3t://", "http:/", "://"};
        String[] authorityInput = {"www.google.com", "go.au", ".1.2.3.4", ""};
        String[] portInput = {":80", ":0", ":-1", ":65a"};

        Random rand = new Random();
        StringBuilder sb;
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

        for (int i = 0; i < 10000; i++) {
            int schemeIndex = rand.nextInt(schemeInput.length);
            int authorityIndex = rand.nextInt(authorityInput.length);
            int portIndex = rand.nextInt(portInput.length);

            sb = new StringBuilder();

            sb.append(schemeInput[schemeIndex]);
            sb.append(authorityInput[authorityIndex]);
            sb.append(portInput[portIndex]);

            testURL(sb.toString(), urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testIsValid ==============\n");
        printResults();
    }

    public void testManualValidator() {
        ResultPair[] testURLS = {
                new ResultPair("https://www.google.com", true),
                new ResultPair("https://google.com", true),
                new ResultPair("http://localhost/", true),
                new ResultPair("https://///www.google.com", false),
                new ResultPair("htps://www.google.com", false),
                new ResultPair("https:google.com", false),
                new ResultPair("http://google.com___.com", false)
        };

        String[] schemes = {"http", "https"};
        UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.ALLOW_LOCAL_URLS);

        for (int i = 0; i < testURLS.length; i++) {
            testURL(testURLS[i].item, urlValidator, validList, invalidList);
        }

        System.out.println("\n\n============== testManualValidator ==============\n");
        printResults(3, 4);
    }
}
