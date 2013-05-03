#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>
#include <vtkXMLImageDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
	// Verify input arguments
// 	if(argc != 2)
// 	{
// 		std::cout << "Usage: " << argv[0]
// 		<< " Filename.vti" << std::endl;
// 		return EXIT_FAILURE;
// 	}

	std::string inputFilename = "volume.vti";

	// Read the file
	vtkSmartPointer<vtkXMLImageDataReader> reader =
		vtkSmartPointer<vtkXMLImageDataReader>::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

	vtkSmartPointer<vtkImageData> data = vtkSmartPointer<vtkImageData>::New();
		data = reader->GetOutput();

	int *dims;
	dims = data->GetDimensions ();
	string filename = ;
	ostringstream os;
	os << "data_" << dims[2] << "_" << dims[1] << "_" << dims[2] << ".raw";

	FILE *fp = fopen(os.str(), "wb");
	for(int k=0; k<dims[0]; k++)
		for(int i=0; i<dims[0]; i++)
			for(int j=0; j<dims[0]; j++)			
				fwrite(data->GetScalarPointer(i, j, k), data->GetScalarSize() , 1, fp);
	fclose(fp);
	cout << data->GetScalarSize ()<<endl;
    cout << dims[0] << " " << dims[1] << " " << dims[2] << endl;

	// Visualize
	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetRepresentationToWireframe();

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->ResetCamera();
	renderer->SetBackground(1,1,1);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}