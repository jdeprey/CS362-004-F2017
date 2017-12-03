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

        System.out.println("============== testSchemePartition ==============\n");
        System.out.println("Expected valid scheme count: " + 4 + ", actual valid scheme count: " + validList.size());
        System.out.println("Expected invalid scheme count: " + 5 + ", actual invalid scheme count: " + invalidList.size());

        System.out.print("Valid schemes: ");
        for (String scheme : validList) {
            System.out.print(scheme + ", ");
        }

        System.out.println();

        System.out.print("Invalid schemes: ");
        for (String scheme : invalidList) {
            System.out.print(scheme + ", ");
        }

        // clean up lists
        validList.clear();
        invalidList.clear();
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

        System.out.println("============== testSchemePartition ==============\n");
        System.out.println("Expected valid authority count: " + 7 + ", actual valid authority count: " + validList.size());
        System.out.println("Expected invalid authority count: " + 12 + ", actual invalid authority count: " + invalidList.size());

        System.out.print("Valid authorities: ");
        for (String auth : validList) {
            System.out.print(auth + ", ");
        }

        System.out.println();

        System.out.print("Invalid authorities: ");
        for (String auth : invalidList) {
            System.out.print(auth + ", ");
        }

        // clean up lists
        validList.clear();
        invalidList.clear();
    }

    public void testPortPartition() {

    }

    public void testPathPartition() {

    }

    public void testQueryPartition() {

    }

    public void testIsValid() {
        for (int i = 0; i < 10000; i++) {

        }
    }

    public void testAnyOtherUnitTest() {

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

        System.out.println("============== testManualValidator ==============\n");
        System.out.println("Expected valid url count: " + 3 + ", actual valid url count: " + validList.size());
        System.out.println("Expected invalid url count: " + 4 + ", actual invalid url count: " + invalidList.size());

        System.out.print("Valid URLS: ");
        for (String url : validList) {
            System.out.print(url + ", ");
        }

        System.out.println();

        System.out.print("Invalid URLS: ");
        for (String url : invalidList) {
            System.out.print(url + ", ");
        }

        // clean up lists
        validList.clear();
        invalidList.clear();
    }


    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */


}