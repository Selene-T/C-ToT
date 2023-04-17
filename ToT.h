#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <thread>

namespace TrackerofTime {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;

	/// <summary>
	/// Summary for ToT
	/// </summary>
	public ref class ToT : public System::Windows::Forms::Form
	{
		public:
			ToT(void)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//
			}

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~ToT()
			{
				if (components)
				{
					delete components;
				}
			}
		private: System::Windows::Forms::Button^ button1;
		private: System::Windows::Forms::Button^ button2;
		protected:

		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container^ components;

	#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->SuspendLayout();
				// 
				// button1
				// 
				this->button1->Location = System::Drawing::Point(329, 339);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(75, 23);
				this->button1->TabIndex = 0;
				this->button1->Text = L"button1";
				this->button1->UseVisualStyleBackColor = true;
				this->button1->Click += gcnew System::EventHandler(this, &ToT::button1_Click);
				// 
				// button2
				// 
				this->button2->Location = System::Drawing::Point(329, 368);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(75, 23);
				this->button2->TabIndex = 1;
				this->button2->Text = L"button2";
				this->button2->UseVisualStyleBackColor = true;
				this->button2->Click += gcnew System::EventHandler(this, &ToT::button2_Click);
				// 
				// ToT
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				this->ClientSize = System::Drawing::Size(522, 464);
				this->Controls->Add(this->button2);
				this->Controls->Add(this->button1);
				this->Name = L"ToT";
				this->Text = L"Tracker of Time";
				this->ResumeLayout(false);

			}
	#pragma endregion

		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			this->BackgroundImage = getResource("inventory");
		}
		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			System::Drawing::Image^ bkup = getResource("inventory");

			cv::Mat img = cv::imread("resources/inventory.bmp");
																															// I have also seen this    vvvv    as "4 * img.rows" instead of img.step 
			System::Drawing::Bitmap^ bimg = gcnew System::Drawing::Bitmap(img.cols, img.rows, img.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img.data));
			this->BackgroundImage = bimg;

			//this->BackgroundImage = gcnew System::Drawing::Bitmap(img.cols, img.rows, img.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, IntPtr(img.data));
			
				// Used to delay a second
			//std::chrono::seconds dura(1);
			//std::this_thread::sleep_for(dura);
		}

		private: System::Drawing::Image^ getResource(System::String^ file) {
			// Easy function call for loading resources
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ToT::typeid));
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(file)));
		}
	};
}
