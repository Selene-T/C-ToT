#include "materials.hpp"
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>

static bool isFirstRun = true;
static cv::Mat allItems[56];

// For the first run, assemble the resources
void firstRun() {	
	// Padding for single digits
	std::string pad0 = "0";

	// Load the resources into allItems[]
	for (int8_t i = 0; i < 56; i++) {
		// Unset the padding when we hit 10
	  if (i > 9) { pad0 = ""; };
	  allItems[i] = cv::imread("resources/item" + pad0 + std::to_string(i) + ".bmp");
	}

	// Unset first run
	isFirstRun = false;
}

// Assemble inventory array into a single image
cv::Mat matInventory(uint8_t items[24]) {

	// Make sure global variables are assigned
	if (isFirstRun) { firstRun(); };
	
	cv::Mat inventoryFull, inventoryRow, inventoryItem, greyscaleItem;

	for (int8_t row = 0; row < 4; row++) {
		for (int8_t col = 0; col < 6; col++) {
			// Catch 0xff, un-acquired items
			if (items[row * 6 + col] == 0xff) {
				// Gather the item slot
				int tempItem = row * 6 + col;
				// Convert the item slot into the base item
				if (tempItem > 21) {
					// Set final 2 (quest items) as eggs
					tempItem = 33;
				}	else if (tempItem > 17) {
					// Set the next final 4 (bottles) as empty bottles
					tempItem = 20;
				} else {
					// Skip over Fairy Ocarina
					if (tempItem > 7) { tempItem++; }
					// Skip over Longshot
					if (tempItem > 10) { tempItem++; }
				}
				// Convert image into greyscale, then back into BGR format to combine in with the others
				cv::cvtColor(allItems[tempItem], greyscaleItem, cv::COLOR_BGR2GRAY);
				cv::cvtColor(greyscaleItem, inventoryItem, cv::COLOR_GRAY2BGR);
			} else {
				// Grab the coloured image
				inventoryItem = allItems[items[row * 6 + col]].clone();
			}

			if (col == 0) {
				// For the first of each row, do a clone to reset its size
				inventoryRow = inventoryItem.clone();
			} else {
				// Combine each item onto the row
				cv::hconcat(inventoryRow, inventoryItem, inventoryRow);
			}
		}

		if (row == 0) {
			// Set initial row into full inventory
			inventoryFull = inventoryRow.clone();
		} else { 
			// Add the row to the full inventory
			cv::vconcat(inventoryFull, inventoryRow, inventoryFull);
		}
	}

	// Return the full inventory
	return inventoryFull;
}