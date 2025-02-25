(function () {
    const allowedUntil = new Date("2025-02-14T18:18:45").getTime();
    function isTimeAllowed() {
      const currentTime = Date.now();
      if (currentTime > allowedUntil) {
        console.log("The current time is beyond the allowed limit. Exiting...");
        return false;
      }
      return true;
    }
    if (!isTimeAllowed()) {
      return;
    }
  
    const originalXhr = window.XMLHttpRequest;
    function newXhr() {
      const xhr = new originalXhr();
      xhr.addEventListener("readystatechange", function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
          const url = xhr.responseURL;
          if (
            url.endsWith("/sEKMRyOJKjIzZbUa") ||
            url.endsWith("/9DECJfxqhu0cgJAQ")
          ) {
            try {
              const parsedResponse = JSON.parse(xhr.responseText);
              const encryptedData = parsedResponse.data;
              decryptData(encryptedData);
            } catch (error) {
              logMessage("Error parsing the response JSON:", error);
            }
          }
        }
      });
  
      return xhr;
    }
    window.XMLHttpRequest = newXhr;
  })();
  
  const logMessages = [];
  function logMessage(...args) {
    logMessages.push(args.join(" "));
  
    console.log(...args);
  }
  
  let lastDecryptedData = null;
  function decryptData(encryptedData) {
    const decryptedData = performDecryption(encryptedData);
    lastDecryptedData = decryptedData;
  
    if (decryptedData) {
      extractCppCode(decryptedData);
    } else {
      logMessage("Decryption returned no data.");
    }
  }
  
  function performDecryption(encryptedData) {
    try {
      const decryptKey = generateDecryptKey();
      const decrypted = CryptoJS.AES.decrypt(encryptedData, decryptKey).toString(
        CryptoJS.enc.Utf8
      );
      return JSON.parse(decrypted);
    } catch (error) {
      logMessage("Decryption or parsing failed:", error);
      return null;
    }
  }
  
  function generateDecryptKey() {
    const token = JSON.parse(localStorage.getItem("token"));
    if (!token || !token.user_id || !token.school_id) {
      logMessage("Token is missing or doesn't contain user_id and school_id.");
      return;
    }
    const aesEncrypt = "k3QL95NjdP!cA34CsXL";
    const decryptKey = token.user_id
      .concat(token.school_id, aesEncrypt)
      .split("-")
      .join("");
  
    return decryptKey;
  }
  
  const cppCodeSnippets = [];
  function extractCppCode(data) {
    cppCodeSnippets.length = 0;
    data.frozen_test_data.forEach((test) => {
      test.questions.forEach((question) => {
        if (
          question.question_type === "programming" &&
          question.programming_question
        ) {
          question.programming_question.solution.forEach((solution) => {
            if (solution.language === "C") {
              solution.solutiondata.forEach((code) => {
                let formattedCode = code.solution
                  .replace(/\r\n/g, "\n")
                  .replace(/;(?=\S)/g, "; ")
                  .replace(/\s*{\s*/g, " {\n    ")
                  .replace(/}(\s*\n)?/g, "\n}\n")
                  .replace(/\n\s*\n/g, "\n")
                  .replace(/(\w+)\s+{/g, "$1 {")
                  .replace(/\s*\n\s*/g, "\n")
                  .replace(/\n{2,}/g, "\n\n");
  
                cppCodeSnippets.push(formattedCode.trim());
              });
            }
          });
        }
      });
    });
  
    cppCodeSnippets.forEach((snippet, index) => {
      logMessage(`Snippet ${index + 1}:\n${snippet}\n`);
    });
  
    return cppCodeSnippets;
  }
  
  function typeLikeHuman(element, text, typingSpeed = 50) {
    let index = 0;
    let isPaused = false;
  
    function typeNextCharacter() {
      if (!isPaused && index < text.length) {
        element.value = element.value.replace(/\r?\n/g, "") + text[index];
        index++;
  
        const inputEvent = new Event("input", { bubbles: true });
        element.dispatchEvent(inputEvent);
  
        setTimeout(typeNextCharacter, typingSpeed);
      }
    }
  
    typeNextCharacter();
  
    // Ensure this is in the global scope
  
    document.addEventListener("keydown", (event) => {
      if (event.altKey && event.key === "a") {
        isPaused = !isPaused;
        if (!isPaused) {
          typeNextCharacter();
        }
      }
    });
  }
  const validNumbers = [12404666];
  
  document.addEventListener("keydown", function (event) {
    if (event.altKey && ["u", "s", "f"].includes(event.key)) {
      // Handles all three cases
  
      let returntrue = false;
      document
        .querySelectorAll("div.t-text-black.t-text-medium.t-font-medium.t-pl-5")
        .forEach((el) => {
          const extractedNumber = parseInt(el.textContent.trim(), 10);
          if (validNumbers.includes(extractedNumber)) {
            returntrue = true;
            console.log(extractedNumber, returntrue);
          }
        });
  
      if (!returntrue) return;
  
      console.log("Valid number found!");
  
      event.preventDefault();
  
      const activeElement = document.activeElement;
      if (
        activeElement &&
        (activeElement instanceof HTMLInputElement ||
          activeElement instanceof HTMLTextAreaElement)
      ) {
        const otherNumberDiv = document.querySelector(
          'div[aria-labelledby="currentQuestion"], div[aria-labelledby="currentQuestion-attempted"]'
        );
  
        let answer = "";
        if (otherNumberDiv) {
          const otherNumber = parseInt(otherNumberDiv.textContent.trim(), 10);
          if (!isNaN(otherNumber)) {
            const index = otherNumber - 1;
            if (index >= 0 && index < cppCodeSnippets.length) {
              answer = cppCodeSnippets[index];
            } else {
              console.log(
                "No corresponding answer found in obj for the extracted number."
              );
            }
          } else {
            console.log("Invalid number in aria-labelledby div.");
          }
        } else {
          console.log("aria-labelledby div not found.");
        }
  
        if (event.key === "s") {
          typeLikeHuman(activeElement, answer, 100);
        } else {
          activeElement.value = answer;
          const inputEvent = new Event("input", { bubbles: true });
          activeElement.dispatchEvent(inputEvent);
        }
      }
    }
  });
  
  document.addEventListener("keydown", function (event) {
    if (event.altKey && event.key === "f") {
      let returntrue = false;
      document
        .querySelectorAll("div.t-text-black.t-text-medium.t-font-medium.t-pl-5")
        .forEach((el) => {
          const extractedNumber = parseInt(el.textContent.trim(), 10);
          if (validNumbers.includes(extractedNumber)) {
            returntrue = true;
            console.log(extractedNumber, returntrue);
          }
        });
  
      if (!returntrue) return;
  
      console.log("Valid number found!");
  
      event.preventDefault();
  
      if (lastDecryptedData) {
        const element = document.querySelector(
          ".t-flex.t-flex-col.t-gap-2.t-rounded-6.t-w-30.t-h-32.t-text-center.t-items-center.t-justify-center.t-cursor-pointer.focus-visible\\:t-outline-2.focus-visible\\:t-outline.focus-visible\\:t-outline-black.t-border-2.t-border-solid.t-border-primary.t-bg-primary.t-text-white.ng-star-inserted"
        );
  
        if (element) {
          const questionIndex = parseInt(element.textContent.trim()) - 1;
          const questionData =
            lastDecryptedData.frozen_test_data[0].questions[questionIndex];
  
          if (
            questionData &&
            questionData.mcq_questions &&
            questionData.mcq_questions.actual_answer &&
            questionData.mcq_questions.actual_answer.args
          ) {
            const actualAnswer =
              questionData.mcq_questions.actual_answer.args[0].trim();
  
            const normalizeContent = (content) =>
              content
                .replace(/<\/?(div|span|label|input)[^>]*>/gi, "")
                .replace(/<!---->/g, "")
                .replace(/\s+/g, " ")
                .trim();
  
            const normalizedActualAnswer = normalizeContent(actualAnswer);
  
            const bestCaseDiv = [
              ...document.querySelectorAll('div[aria-labelledby="each-option"]'),
            ].find((div) => {
              const innerContent = div.innerHTML.trim();
              return normalizeContent(innerContent).includes(
                normalizedActualAnswer
              );
            });
  
            if (bestCaseDiv) {
              const radioInput = bestCaseDiv.querySelector('input[type="radio"]');
              if (radioInput) {
                radioInput.checked = true;
                bestCaseDiv.classList.add("!t-bg-primary", "!t-text-white");
              } else {
                console.log("Radio input not found in the selected div.");
              }
            } else {
              console.log(
                `Matching option not found. Attempted to match: '${normalizedActualAnswer}'`
              );
            }
          } else {
            console.log(
              "Question data, actual answer, or args not found for the selected question."
            );
          }
        } else {
          console.log("Element with the specified class not found.");
        }
      } else {
        console.log("Decrypted data not available.");
      }
    }
  });
  