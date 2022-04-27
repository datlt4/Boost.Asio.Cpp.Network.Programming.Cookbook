# Chapter 1 - I/O Operations

## Introduction

- **I/O operations** là các hoạt động chính trong cơ sở hạ tầng mạng của bất kỳ ứng dụng phân tán nào. Chúng trực tiếp tham gia vào **process** trao đổi dữ liệu. Các hoạt động đầu vào được sử dụng để nhận dữ liệu từ các ứng dụng từ xa, trong khi các hoạt động đầu ra cho phép gửi dữ liệu đến chúng.

### I/O buffers

- Lập trình mạng là tổ chức giao tiếp giữa các **process** trên một mạng máy tính. Giao tiếp trong ngữ cảnh này ngụ ý trao đổi dữ liệu giữa hai hoặc nhiều **process**. Từ quan điểm của một **process** tham gia vào giao tiếp như vậy, **process** thực hiện các hoạt động **I/O**, gửi và nhận dữ liệu từ các **process** tham gia khác.

- Giống như bất kỳ loại **I/O** nào khác, **I/O** mạng liên quan đến việc sử dụng bộ đệm bộ nhớ, là các khối bộ nhớ liền kề được cấp phát trong không gian địa chỉ của **process** được sử dụng để lưu trữ dữ liệu. Khi thực hiện bất kỳ loại thao tác nhập liệu nào (ví dụ: đọc một số dữ liệu từ tệp, đường dẫn hoặc máy tính từ xa qua mạng), dữ liệu đến **process** và phải được lưu trữ ở đâu đó trong không gian địa chỉ của nó để dữ liệu có sẵn. Trước khi thực hiện thao tác nhập, bộ đệm được cấp phát và sau đó được sử dụng làm điểm đích dữ liệu trong **process** hoạt động. Khi hoàn tất thao tác nhập, bộ đệm chứa dữ liệu đầu vào, ứng dụng có thể xử lý dữ liệu này. Tương tự như vậy, trước khi thực hiện hoạt động đầu ra, dữ liệu phải được chuẩn bị và đưa vào bộ đệm đầu ra, sau đó được sử dụng trong hoạt động đầu ra, nơi nó đóng vai trò là nguồn dữ liệu.

- Rõ ràng, bộ đệm là thành phần thiết yếu của bất kỳ ứng dụng nào thực hiện bất kỳ loại **I/O** nào, bao gồm cả **I/O** mạng. Đó là lý do tại sao điều quan trọng đối với nhà phát triển, những người phát triển một ứng dụng phân tán là phải biết cách phân bổ và chuẩn bị các bộ đệm **I/O** để sử dụng chúng trong các hoạt động **I/O**.

### Synchronous and asynchronous I/O operations

- **Boost.Asio** hỗ trợ hai loại hoạt động **I/O**: đồng bộ và không đồng bộ. Các hoạt động đồng bộ chặn luồng thực thi gọi chúng và chỉ bỏ chặn khi hoạt động kết thúc. Do đó, tên của loại hoạt động này: đồng bộ.

- Loại thứ hai là hoạt động không đồng bộ. Khi một hoạt động không đồng bộ được bắt đầu, nó được liên kết với một hàm **callback**, được gọi bởi thư viện **Boost.Asio** khi hoạt động kết thúc. Các loại hoạt động **I/O** này cung cấp tính linh hoạt cao, nhưng có thể làm code phức tạp đáng kể. Việc không chặn luồng thực thi cho phép chúng ta sử dụng luồng để chạy các tác vụ khác, trong khi hoạt động không đồng bộ đang được chạy ở chế độ nền.

### Additional operations

- Ngoài ra, chúng ta sẽ xem xét các hoạt động như hủy hoạt động không đồng bộ, tắt và đóng **socket**.

- Khả năng hủy bỏ một hoạt động không đồng bộ đã khởi tạo trước đó là rất quan trọng. Nó cho phép ứng dụng tuyên bố rằng hoạt động đã khởi tạo trước đó không còn liên quan nữa, điều này có thể tiết kiệm tài nguyên của ứng dụng (cả CPU và bộ nhớ), nếu không (trong trường hợp, hoạt động sẽ tiếp tục thực hiện ngay cả sau khi biết rằng không ai quan tâm trong đó nữa) sẽ không thể tránh khỏi lãng phí.

- Tắt socket rất hữu ích nếu cần một phần của ứng dụng phân tán để thông báo cho phần kia rằng toàn bộ thông báo đã được gửi đi, khi giao thức tầng ứng dụng không cung cấp cho chúng ta các phương tiện khác để chỉ ra ranh giới thông báo.

- Như với bất kỳ tài nguyên hệ điều hành nào khác, một **socket** phải được trả lại cho hệ điều hành khi ứng dụng không cần nó nữa. Một hoạt động **closing** cho phép chúng ta làm như vậy.

---

## Using fixed length I/O buffers

- Bộ đệm **I/O** có độ dài cố định thường được sử dụng với các hoạt động **I/O** và đóng vai trò là nguồn dữ liệu hoặc đích khi biết kích thước của thông báo được gửi hoặc nhận. 

- Trong Boost.Asio, một bộ đệm có độ dài cố định được đại diện bởi một trong hai lớp `asio::mutable_buffer` hoặc `asio::const_buffer`. Cả hai lớp này đại diện cho một khối bộ nhớ liền kề được xác định bởi địa chỉ của byte đầu tiên của khối và kích thước của nó tính bằng byte. Như tên của các lớp này gợi ý, `asio::mutable_buffer` đại diện cho một bộ đệm có thể ghi, trong khi `asio::const_buffer` đại diện cho một chỉ đọc.

- Tuy nhiên, cả lớp `asio::mutable_buffer` và `asio::const_buffer` đều không được sử dụng trực tiếp trong các hàm và phương thức **I/O** Boost.Asio. Thay vào đó, các khái niệm `MutableBufferSequence` và `ConstBufferSequence` được giới thiệu.

- Khái niệm `MutableBufferSequence` chỉ định một đối tượng đại diện cho tập hợp các đối tượng `asio::mutable_buffer`. Tương ứng, khái niệm `ConstBufferSequence` chỉ định một đối tượng đại diện cho tập hợp các đối tượng `asio::const_buffer`. Các hàm và phương thức Boost.Asio thực hiện các hoạt động **I/O** chấp nhận các đối tượng thỏa mãn các yêu cầu của khái niệm `MutableBufferSequence` hoặc `ConstBufferSequence` làm đối số của chúng đại diện cho bộ đệm

- Mặc dù trong hầu hết các trường hợp sử dụng, một bộ đệm duy nhất tham gia vào một thao tác **I/O** duy nhất, trong một số trường hợp cụ thể (ví dụ: trong môi trường hạn chế bộ nhớ), nhà phát triển có thể muốn sử dụng một bộ đệm tổng hợp bao gồm nhiều đơn giản nhỏ hơn bộ đệm được phân phối trên không gian địa chỉ của quá trình. Các chức năng và phương thức **I/O** Boost.Asio được thiết kế để hoạt động với các bộ đệm tổng hợp được biểu thị như một tập hợp các bộ đệm đáp ứng các yêu cầu của khái niệm `MutableBufferSequence` hoặc `ConstBufferSequence`.

- Ví dụ, một đối tượng của lớp `std::vector<asio::mutable_buffer>` đáp ứng các yêu cầu của khái niệm `MutableBufferSequence` và do đó, nó có thể được sử dụng để biểu diễn bộ đệm tổng hợp trong các hàm và phương thức liên quan đến **I/O**.

- Vì vậy, bây giờ chúng ta biết rằng nếu chúng ta có một bộ đệm được đại diện như một đối tượng của lớp `asio::mutable_buffer` hoặc `asio::const_buffer`, chúng ta vẫn không thể sử dụng nó với các hàm hoặc phương thức liên quan đến **I/O** do Boost.Asio cung cấp. Bộ đệm phải được biểu diễn dưới dạng một đối tượng, đáp ứng các yêu cầu của khái niệm `MutableBufferSequence` hoặc `ConstBufferSequence` tương ứng. Để làm điều này, ví dụ, chúng ta có thể tạo một tập hợp các đối tượng đệm bao gồm một bộ đệm duy nhất bằng cách khởi tạo một đối tượng của lớp `std::vector<asio::mutable_buffer>` và đặt đối tượng đệm của chúng ta vào đó. Bây giờ bộ đệm là một phần của bộ sưu tập, việc đáp ứng các yêu cầu của `MutableBufferSequence` có thể được sử dụng trong các hoạt động **I/O**.

- Tuy nhiên, mặc dù phương pháp này tốt để tạo bộ đệm tổng hợp bao gồm hai hoặc nhiều bộ đệm đơn giản, nhưng nó trông quá phức tạp khi thực hiện các tác vụ đơn giản như biểu diễn một bộ đệm đơn giản để có thể sử dụng với Boost. các chức năng hoặc phương thức. May mắn thay, Boost.Asio cung cấp cho chúng ta một cách để đơn giản hóa việc sử dụng các bộ đệm đơn với các chức năng và phương thức liên quan đến **I/O**.

- Hàm `asio::buffer()` free có 28 dạng biểu diễn của bộ đệm và trả về một đối tượng của các lớp `asio::mutable_buffers_1` hoặc `asio::const_buffers_1`. Nếu đối số bộ đệm được truyền cho hàm `asio::buffer()` là kiểu chỉ đọc, thì hàm trả về một đối tượng của lớp `asio::const_buffers_1`; nếu không, một đối tượng của lớp `asio::mutable_buffers_1` được trả về.

- Các lớp `asio::mutable_buffers_1` và `asio::const_buffers_1` tương ứng là bộ điều hợp của các lớp `asio::mutable_buffer` và `asio::const_buffer`. Chúng cung cấp một giao diện và hành vi đáp ứng các yêu cầu của các khái niệm `MutableBufferSequence` và `ConstBufferSequence`, cho phép chúng ta chuyển các bộ điều hợp này làm đối số cho các hàm và phương thức **I/O** Boost.Asio.

- Chúng ta hãy xem xét hai thuật toán và các mẫu mã tương ứng mô tả cách chuẩn bị một bộ đệm bộ nhớ có thể được sử dụng với các hoạt động **I/O** Boost.Asio. Thuật toán đầu tiên xử lý các bộ đệm dự định được sử dụng cho hoạt động đầu ra và thuật toán thứ hai được sử dụng cho hoạt động đầu vào.

### Preparing a buffer for an output operation

- Cách chuẩn bị một bộ đệm có thể được sử dụng với phương thức của **socket** Boost.Asio thực hiện hoạt động đầu ra như `asio::ip::tcp::socket::send()` hoặc `asio::write()`:

    - Cấp phát một bộ đệm. Lưu ý rằng bước này không liên quan đến bất kỳ chức năng hoặc kiểu dữ liệu nào từ Boost.Asio.

    - Điền vào bộ đệm với dữ liệu sẽ được sử dụng làm đầu ra.

    - Biểu diễn vùng đệm như một đối tượng thỏa mãn các yêu cầu của khái niệm `ConstBufferSequence`.

    - Bộ đệm đã sẵn sàng để sử dụng với các phương thức và chức năng đầu ra Boost.Asio.

[**CODE**](asio-example/chapter-2/FixedLengthBufferOutput.cpp) - Biểu diễn các bộ đệm có độ dài cố định để chúng có thể được sử dụng với các hoạt động **I/O** Boost.Asio.

### Preparing a buffer for an input operation

- Cách chuẩn bị bộ đệm có thể được sử dụng với phương thức của socket Boost.Asios thực hiện thao tác nhập như `asio::ip::tcp::socket::accept()` hoặc `asio::read()`:

    - Cấp phát một bộ đệm. Kích thước của bộ đệm phải đủ lớn để phù hợp với khối dữ liệu được nhận. Lưu ý rằng bước này không liên quan đến bất kỳ chức năng hoặc kiểu dữ liệu nào từ Boost.Asio.

    - Biểu diễn bộ đệm bằng cách sử dụng một đối tượng thỏa mãn các yêu cầu của khái niệm `MutableBufferSequence`.

    - Bộ đệm đã sẵn sàng để sử dụng với các chức năng và phương thức nhập Boost.Asio.

[**CODE**](asio-example/chapter-2/FixedLengthBufferInput.cpp) - Chuẩn bị một bộ đệm nơi dữ liệu sẽ được lưu trữ.

---

## Using extensible stream-oriented I/O buffers

- Bộ đệm mở rộng là những bộ đệm tự động tăng kích thước của chúng khi dữ liệu mới được ghi vào chúng. Chúng thường được sử dụng để đọc dữ liệu từ các socket khi kích thước của tin nhắn đến là không xác định.

- Một số giao thức lớp ứng dụng không xác định kích thước chính xác của thông báo. Thay vào đó, ranh giới của thông báo được biểu thị bằng một chuỗi ký hiệu cụ thể ở cuối thông điệp hoặc bằng thông điệp dịch vụ giao thức truyền tải cuối tệp `(EOF)` do người gửi đưa ra sau khi gửi xong thông báo.

- Ví dụ: theo giao thức `HTTP`, phần tiêu đề của thông báo yêu cầu và phản hồi không có độ dài cố định và ranh giới của nó được biểu thị bằng một chuỗi bốn ký hiệu ASCII,`<CR><LF><CR><LF>`, là một phần của thông báo. Trong những trường hợp như vậy, các bộ đệm và chức năng có thể mở rộng động có thể hoạt động với chúng, được cung cấp bởi thư viện Boost.Asio, rất hữu ích.

- Extensible stream-oriented buffers được biểu diễn trong Boost.Asio với lớp `asio::streambuf`, là một `typedef` cho `asio::basic_streambuf`:

```cpp
typedef basic_streambuf<> streambuf;
```

- Lớp `asio::basic_streambuf<>` được kế thừa từ `std::streambuf`, có nghĩa là nó có thể được sử dụng làm bộ đệm luồng cho các lớp luồng STL. Ngoài ra, một số chức năng **I/O** được cung cấp bởi Boost.Asio xử lý các bộ đệm được biểu diễn dưới dạng các đối tượng của lớp này.

- Chúng ta có thể làm việc với một đối tượng của lớp `asio::streambuf` giống như chúng ta sẽ làm việc với bất kỳ lớp đệm luồng nào được kế thừa từ lớp `std::streambuf`. Ví dụ: chúng ta có thể gán đối tượng này cho một luồng (ví dụ: `std::istream`, `std::ostream` hoặc `std::iostream`, tùy thuộc vào nhu cầu của chúng ta) và sau đó, sử dụng toán tử `operator<<()` và `operator>>()` để ghi và đọc dữ liệu đến và từ luồng.

[**CODE**](asio-example/chapter-2/ExtensibleStreamOrientedBuffer.cpp) - Một ứng dụng mẫu trong đó một đối tượng của `asio::streambuf` được khởi tạo, một số dữ liệu được ghi vào nó và sau đó dữ liệu được đọc ngược lại từ bộ đệm đến một đối tượng của lớp `std::string`.

---

## Writing to a TCP socket synchronously

- Ghi vào **socket** TCP là một hoạt động output được sử dụng để gửi dữ liệu đến điều khiển từ xa ứng dụng được kết nối với **socket** này. Ghi đồng bộ là cách đơn giản nhất để gửi dữ liệu sử dụng **socket** do Boost.Asio cung cấp. Các phương pháp và chức năng thực hiện đồng bộ ghi vào socket chặn luồng thực thi và không trả lại cho đến khi dữ liệu (ít nhất một số lượng dữ liệu) được ghi vào **socket** hoặc xảy ra lỗi.

- Cách cơ bản nhất để ghi vào socket được cung cấp bởi thư viện Boost.Asio là sử dụng phương thức `write_some()` của lớp `asio::ip::tcp::socket`. Đây là khai báo về một trong các quá tải của phương thức:

```cpp
template<typename ConstBufferSequence>
std::size_t write_some(const ConstBufferSequence & buffers);
```

- Phương thức này chấp nhận một đối tượng đại diện cho bộ đệm tổng hợp làm đối số và như tên gọi của nó, ghi một số lượng dữ liệu từ bộ đệm vào socket. Nếu phương thức thành công, giá trị trả về cho biết số byte được ghi. Điểm cần nhấn mạnh ở đây là phương thức **có thể không gửi tất cả** dữ liệu được cung cấp cho nó thông qua đối số bộ đệm. Phương pháp này chỉ **đảm bảo rằng ít nhất một byte** sẽ được ghi nếu lỗi không xảy ra. Điều này có nghĩa là, trong trường hợp chung, để ghi tất cả dữ liệu từ bộ đệm vào socket, chúng ta có thể cần gọi phương thức này nhiều lần.

- Các bước cần thiết để ghi đồng bộ dữ liệu vào TCP socket trong một ứng dụng phân tán:

    - Trong ứng dụng khách, cấp phát, mở và kết nối một **socket** TCP đang hoạt động. Trong ứng dụng máy chủ, hãy lấy **socket** TCP hoạt động được kết nối bằng cách chấp nhận yêu cầu kết nối bằng **acceptor socket**.
    
    - Phân bổ bộ đệm và lấp đầy nó bằng dữ liệu sẽ được ghi vào socket.
    
    - Trong một vòng lặp, hãy gọi phương thức `write_some()` của socket nhiều lần nếu cần để gửi tất cả dữ liệu có sẵn trong bộ đệm.

[**CODE**](asio-example/chapter-2/WritingToTCPSockSync.cpp) - Client application.

### `asio::write`

- Việc ghi vào socket bằng phương thức `write_some()` của socket có vẻ rất phức tạp đối với một thao tác đơn giản như vậy. Ngay cả khi chúng ta muốn gửi một tin nhắn nhỏ bao gồm một số byte, chúng ta phải sử dụng một vòng lặp, một biến để theo dõi xem có bao nhiêu byte đã được viết và tạo bộ đệm đúng cách cho mỗi lần lặp lại của vòng lặp. Cách tiếp cận này dễ xảy ra lỗi và làm cho mã khó hiểu hơn.

- May mắn thay, Boost.Asio cung cấp một chức năng miễn phí, giúp đơn giản hóa việc ghi vào socket. Hàm này được gọi là `asio::write()`. Chúng ta hãy xem xét một trong những tình trạng quá tải của nó:

```cpp
template<typename SyncWriteStream, typename ConstBufferSequence>
std::size_t write(SyncWriteStream & s, const ConstBufferSequence & buffers);
```

- Hàm này chấp nhận hai đối số. Đầu tiên trong số chúng có tên là s là một tham chiếu đến một đối tượng thỏa mãn các yêu cầu của khái niệm `SyncWriteStream`. Để có danh sách đầy đủ các yêu cầu, hãy tham khảo phần tài liệu Boost.Asio tương ứng tại http://www.boost.org/doc/libs/1_58_0/doc/html/boost_asio/reference/SyncWriteStream.html. Đối tượng của lớp `asio::ip::tcp::socket` đại diện cho một **socket** TCP đáp ứng các yêu cầu này và do đó, có thể được sử dụng làm đối số đầu tiên của hàm. Đối số thứ hai có tên là bộ đệm đại diện cho bộ đệm (đơn giản hoặc hỗn hợp) và chứa dữ liệu sẽ được ghi vào **socket**.

- Ngược lại với phương thức `write_some()` của đối tượng socket ghi một số lượng dữ liệu từ vùng đệm vào socket, hàm `asio::write()` ghi tất cả dữ liệu có sẵn trong vùng đệm. Điều này đơn giản hóa việc ghi vào socket và làm cho mã ngắn hơn và sạch hơn.

---

## Reading from a TCP socket synchronously

- Đọc từ **socket** TCP là một thao tác đầu vào được sử dụng để nhận dữ liệu được gửi bởi ứng dụng từ xa được kết nối với **socket** này. Đọc đồng bộ là cách đơn giản nhất để nhận dữ liệu bằng cách sử dụng **socket** do Boost.Asio cung cấp. Các phương thức và chức năng thực hiện đọc đồng bộ từ socket sẽ chặn luồng thực thi và không trả về cho đến khi dữ liệu (ít nhất là một số lượng dữ liệu) được đọc từ socket hoặc lỗi xảy ra.

- Cách cơ bản nhất để đọc dữ liệu từ socket được cung cấp bởi thư viện Boost.Asio là phương thức `read_some()` của lớp `asio::ip::tcp::socket`. Hãy xem xét một trong những quá tải của phương thức:

```cpp
template<typename MutableBufferSequence>
std::size_t read_some(const MutableBufferSequence & buffers);
```

- Phương thức này chấp nhận một đối tượng đại diện cho bộ đệm có thể ghi (đơn hoặc tổng hợp) làm đối số và như tên gọi của nó, đọc một số lượng dữ liệu từ **socket** vào bộ đệm. Nếu phương thức thành công, giá trị trả về cho biết số byte được đọc. Điều quan trọng cần lưu ý là không có cách nào để kiểm soát phương thức sẽ đọc bao nhiêu byte. Phương pháp này chỉ đảm bảo rằng ít nhất một byte sẽ được đọc nếu lỗi không xảy ra. Điều này có nghĩa là, trong trường hợp chung, để đọc một lượng dữ liệu nhất định từ socket, chúng ta có thể cần gọi phương thức nhiều lần.

- Các bước cần thiết để đọc đồng bộ dữ liệu từ **socket** TCP trong một ứng dụng phân tán:

    - Trong ứng dụng khách, cấp phát, mở và kết nối một **socket** TCP đang hoạt động. Trong ứng dụng máy chủ, hãy lấy **socket** TCP hoạt động được kết nối bằng cách chấp nhận yêu cầu kết nối bằng **socket** bộ chấp nhận.

    - Phân bổ bộ đệm có kích thước vừa đủ để phù hợp với thông điệp dự kiến sẽ đọc.

    - Trong một vòng lặp, hãy gọi phương thức `read_some()` của socket nhiều lần nếu cần để đọc thông báo.

[**CODE**](asio-example/chapter-2/ReadingFromTCPSockSync.cpp)

### `asio::read()`

```cpp
template<typename SyncReadStream, typename MutableBufferSequence>
std::size_t read(SyncReadStream & s, const MutableBufferSequence & buffers);
```

### `asio::read_until()`

```cpp
template<typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream & s, boost::asio::basic_streambuf< Allocator > & b, char delim);
```

###  `asio::read_at()`

- The `asio::read_at()` function provides a way to read data from a socket, starting at a particular offset.

---

## Writing to a TCP socket asynchronously

- Ghi không đồng bộ là một cách linh hoạt và hiệu quả để gửi dữ liệu đến một ứng dụng từ xa.

- Công cụ cơ bản nhất được sử dụng để ghi dữ liệu không đồng bộ vào socket được cung cấp bởi thư viện `Boost.Asio` là phương thức `async_write_some()` của lớp `asio::ip::tcp::socket`.

```cpp
template<typename ConstBufferSequence, typename WriteHandler>
void async_write_some(const ConstBufferSequence & buffers, WriteHandler handler);
```

- Phương thức này bắt đầu thao tác ghi và trả về ngay lập tức. Nó chấp nhận một đối tượng đại diện cho bộ đệm chứa dữ liệu được ghi vào socket làm đối số đầu tiên của nó. Đối số thứ hai là một lệnh **callback**, sẽ được gọi bởi Boost.Asio khi một hoạt động được khởi tạo hoàn tất. Đối số này có thể là một con trỏ hàm, hàm hoặc bất kỳ đối tượng nào khác đáp ứng các yêu cầu của khái niệm **WriteHandler**.

- The callback should have the following signature:

```cpp
void write_handler(const boost::system::error_code& ec, std::size_t bytes_transferred);
```

- Ở đây, `ec` là đối số cho biết mã lỗi nếu một mã xảy ra và đối số `byte_transferred` cho biết có bao nhiêu byte đã được ghi vào socket trong hoạt động không đồng bộ tương ứng.

- Như tên của phương thức `async_write_some()` cho thấy, nó bắt đầu một hoạt động nhằm mục đích ghi một số lượng dữ liệu từ bộ đệm vào socket. Phương thức này **đảm bảo rằng ít nhất một byte** sẽ được ghi trong quá trình hoạt động không đồng bộ tương ứng nếu lỗi không xảy ra. Điều này có nghĩa là, trong trường hợp chung, để ghi tất cả dữ liệu có sẵn trong bộ đệm vào socket, chúng ta có thể cần thực hiện thao tác không đồng bộ này vài lần.

- Bây giờ chúng ta đã biết phương thức này hoạt động như thế nào, hãy xem cách triển khai một ứng dụng thực hiện việc ghi không đồng bộ vào socket.

- Các bước cần thiết để thực hiện và triển khai một ứng dụng, ứng dụng này sẽ ghi dữ liệu vào TCP socket một cách không đồng bộ. Lưu ý rằng thuật toán này cung cấp một cách khả thi để triển khai một ứng dụng như vậy. Boost.Asio khá linh hoạt và cho phép chúng ta tổ chức và cấu trúc ứng dụng bằng cách ghi dữ liệu vào socket một cách không đồng bộ theo nhiều cách khác nhau:

    - Định nghĩa cấu trúc dữ liệu có chứa một con trỏ tới một đối tượng socket, một bộ đệm và một biến được sử dụng như một bộ đếm số byte được viết.

    - Xác định một hàm **callback** sẽ được gọi khi hoàn thành thao tác ghi không đồng bộ.

    - Trong một ứng dụng khách, phân bổ và mở một **socket** TCP đang hoạt động và kết nối nó với một ứng dụng từ xa. Trong một ứng dụng máy chủ, hãy lấy một **socket** TCP đang hoạt động được kết nối bằng cách chấp nhận một yêu cầu kết nối.
    
    - Phân bổ một bộ đệm và điền vào nó bằng dữ liệu sẽ được ghi vào socket.

    - Bắt đầu hoạt động ghi không đồng bộ bằng cách gọi phương thức `async_write_some()` của socket. Chỉ định một chức năng được xác định ở bước 2 làm lệnh **callback**.

    - Gọi phương thức `run()` trên một đối tượng của lớp `asio::io_service`.

    - Trong một lệnh **callback**, hãy tăng bộ đếm số byte được viết. Nếu số byte được ghi ít hơn tổng số byte được ghi, hãy bắt đầu thao tác ghi không đồng bộ mới để ghi phần tiếp theo của dữ liệu.

[**CODE**](asio-example/chapter-2/WritingToTCPSockAsync.cpp) - Ứng dụng khách mẫu thực hiện ghi (`async_write_some`) không đồng bộ theo thuật toán.

[**CODE**](asio-example/chapter-2/WritingToTCPSockAsyncEnhanced.cpp) - Ứng dụng khách mẫu thực hiện ghi (`async_write`) không đồng bộ theo thuật toán.

- Chúng ta chỉ định cùng một hàm `callback()` bằng cách sử dụng hàm `std::bind()` để đính kèm một đối số bổ sung - đối tượng `Session`, giống như chúng ta đã làm khi chúng ta bắt đầu hoạt động không đồng bộ đầu tiên.

- Các chu kỳ bắt đầu hoạt động ghi không đồng bộ và lệnh **callback** do đó lặp lại cho đến khi tất cả dữ liệu từ bộ đệm được ghi vào socket hoặc lỗi xảy ra.

- Khi hàm **callback** trả về mà không bắt đầu hoạt động không đồng bộ mới, phương thức `asio::io_service::run()` được gọi trong hàm `main()`, bỏ chặn luồng thực thi và trả về. Hàm `main()` cũng trả về. Đây là khi ứng dụng thoát.

---

## Reading from a TCP socket asynchronously

- Asynchronous reading is a flexible and efficient way to receive data from a remote application.

- The most basic tool used to asynchronously read data from a TCP socket provided by the Boost.Asio library is the `async_read_some()` method of the `asio::ip::tcp::socket` class.

```cpp
template<typename MutableBufferSequence, typename ReadHandler>
void async_read_some(const MutableBufferSequence & buffers, ReadHandler handler);
```

- Phương thức này bắt đầu hoạt động đọc không đồng bộ và trả về ngay lập tức. Nó chấp nhận một đối tượng đại diện cho bộ đệm có thể thay đổi làm đối số đầu tiên của nó mà dữ liệu sẽ được đọc từ socket. Đối số thứ hai là một lệnh **callback** được gọi bởi Boost.Asio khi hoạt động hoàn tất. Đối số này có thể là một con trỏ hàm, một hàm hoặc bất kỳ đối tượng nào khác đáp ứng các yêu cầu của khái niệm `ReadHandler`.

- **Callback** phải có cú pháp sau:

```cpp
void read_handler (const boost::system::error_code & ec, std::size_t bytes_transferred);
```

- Ở đây, `ec` là một đối số thông báo mã lỗi nếu một mã xảy ra và đối số `byte_transferred` cho biết có bao nhiêu byte đã được đọc từ socket trong hoạt động không đồng bộ tương ứng.

- Như tên của phương thức `async_read_some()` cho thấy, nó bắt đầu một hoạt động nhằm đọc một số lượng dữ liệu từ socket vào bộ đệm. Phương pháp này **đảm bảo rằng ít nhất một byte** sẽ được đọc trong quá trình hoạt động không đồng bộ tương ứng nếu lỗi không xảy ra. Điều này có nghĩa là, trong trường hợp chung, để đọc tất cả dữ liệu từ socket, chúng ta có thể cần thực hiện thao tác không đồng bộ này vài lần.

- Bây giờ chúng ta đã biết phương thức khóa hoạt động như thế nào, hãy xem cách triển khai một ứng dụng thực hiện đọc không đồng bộ từ socket.

- Thuật toán sau đây mô tả các bước cần thiết để triển khai một ứng dụng, ứng dụng này đọc dữ liệu từ một **socket** một cách không đồng bộ. Lưu ý rằng thuật toán này cung cấp một cách khả thi để triển khai một ứng dụng như vậy. Boost.Asio khá linh hoạt và cho phép chúng tôi tổ chức và cấu trúc ứng dụng bằng cách đọc dữ liệu từ một socket một cách không đồng bộ theo những cách khác nhau:

    - Định nghĩa cấu trúc dữ liệu chứa một con trỏ đến đối tượng socket, một bộ đệm, một biến xác định kích thước của bộ đệm và một biến dùng làm bộ đếm số byte đọc được.

    - Định nghĩa một hàm **callback** sẽ được gọi khi hoàn thành thao tác đọc không đồng bộ.

    - Trong một ứng dụng khách, phân bổ và mở một **socket** TCP đang hoạt động, sau đó, kết nối nó với một ứng dụng từ xa. Trong một ứng dụng máy chủ, hãy lấy một **socket** TCP đang hoạt động được kết nối bằng cách chấp nhận một yêu cầu kết nối.

    - Phân bổ một bộ đệm đủ lớn để thông báo dự kiến ​​vừa với.

    - Bắt đầu hoạt động đọc không đồng bộ bằng cách gọi phương thức `async_read_some()` của socket, chỉ định một hàm được định nghĩa ở bước 2 như một lệnh **callback**.

    - Gọi phương thức `run()` trên một đối tượng của lớp `asio::io_service`.

    - Khi gọi **callback**, hãy tăng bộ đếm số byte đã đọc. Nếu số byte được đọc ít hơn tổng số byte được đọc (nghĩa là kích thước của một thông báo dự kiến), hãy bắt đầu thao tác đọc không đồng bộ mới để đọc phần dữ liệu tiếp theo.

---

## Canceling asynchronous operations

- Một tình huống là khi ứng dụng khách gửi yêu cầu đến ứng dụng máy chủ và bắt đầu chờ thông báo phản hồi, nhưng ứng dụng máy chủ trong khi xử lý yêu cầu của khách lại gặp bế tắc do lỗi trong đó. Trong trường hợp này, người dùng sẽ phải đợi thông báo phản hồi mãi mãi và sẽ không bao giờ nhận được.

- Một trong những lợi ích của các hoạt động không đồng bộ được cung cấp bởi thư viện Boost.Asio là chúng có thể bị hủy bất kỳ lúc nào sau khi bắt đầu.

- Các bước cần thiết để bắt đầu và hủy các hoạt động không đồng bộ với Boost.Asio:

    - Nếu ứng dụng dự định chạy trên Windows XP hoặc Windows Server 2003, hãy xác định các cờ cho phép hủy hoạt động không đồng bộ trên các phiên bản Windows này.

    - Phân bổ và mở **socket** TCP hoặc UDP. Nó có thể là một **activate socket** hoặc **passive socket** trong ứng dụng máy khách hoặc máy chủ.

    - Xác định một hàm **callback** cho một hoạt động không đồng bộ. Nếu cần, trong lần **callback** này, hãy triển khai một đoạn code để xử lý tình huống khi hoạt động đã bị hủy.

    - Khởi tạo một hoặc nhiều hoạt động không đồng bộ và chỉ định một chức năng hoặc một đối tượng được xác định trong bước 4 dưới dạng một lệnh **callback**.

    - Sinh ra một thread và sử dụng nó để chạy vòng lặp sự kiện Boost.Asio.

    - Gọi phương thức `cancel()` trên đối tượng socket để hủy bỏ tất cả các hoạt động không đồng bộ còn tồn tại liên quan đến socket này.

[**CODE**](asio-example/chapter-2/CancellingAsyncOperations.cpp) - Hãy xem xét việc triển khai ứng dụng khách được thiết kế phù hợp với thuật toán đã trình bày, trong đó hoạt động kết nối không đồng bộ được khởi tạo đầu tiên và sau đó bị hủy bỏ.

---

## Shutting down and closing a socket

- Trong một số ứng dụng phân tán giao tiếp qua giao thức TCP, cần phải chuyển các thông điệp không có kích thước cố định và chuỗi byte cụ thể, đánh dấu ranh giới của nó. Điều này có nghĩa là bên nhận, trong khi đọc thông báo từ **socket**, không thể xác định vị trí thông báo kết thúc bằng cách phân tích chính thông điệp với kích thước hoặc nội dung của nó.

- Một cách tiếp cận để giải quyết vấn đề này là cấu trúc mỗi thông báo theo cách mà nó bao gồm phần tiêu đề hợp lý và phần nội dung hợp lý. Phần tiêu đề có kích thước và cấu trúc cố định và chỉ định kích thước của phần nội dung. Điều này cho phép phía nhận lần đầu tiên đọc và phân tích cú pháp tiêu đề, tìm ra kích thước của nội dung thư, sau đó đọc đúng phần còn lại của thư.

- Cách làm này khá đơn giản và được nhiều người áp dụng. Tuy nhiên, nó mang lại một số dư thừa và chi phí tính toán bổ sung, điều này có thể không được chấp nhận trong một số trường hợp. Ý tưởng của cách tiếp cận này là để người gửi tin nhắn tắt phần gửi của socket sau khi tin nhắn được ghi vào socket. Điều này dẫn đến một tin nhắn dịch vụ đặc biệt được gửi đến người nhận, thông báo cho người nhận rằng tin nhắn đã kết thúc và người gửi sẽ không gửi bất cứ thứ gì khác bằng cách sử dụng kết nối hiện tại.

- Cách tiếp cận thứ hai cung cấp nhiều lợi ích hơn so với cách tiếp cận đầu tiên và bởi vì nó là một phần của phần mềm giao thức TCP, nó có sẵn cho nhà phát triển để sử dụng.

- Một hoạt động khác trên **socket**, đó là, **closing** có vẻ tương tự như tắt máy, nhưng thực ra nó rất khác với nó. Việc đóng một **socket** giả định trả lại **socket** và tất cả các tài nguyên khác được liên kết với nó trở lại hệ điều hành. Cũng giống như bộ nhớ, một tiến trình hoặc một luồng, một tệp xử lý hoặc một mutex, một **socket** là tài nguyên của một hệ điều hành. Và giống như bất kỳ tài nguyên nào khác, một **socket** sẽ được trả lại cho hệ điều hành sau khi nó đã được cấp phát, sử dụng và ứng dụng không cần nữa. Nếu không, rò rỉ tài nguyên có thể xảy ra, cuối cùng có thể dẫn đến cạn kiệt tài nguyên và dẫn đến lỗi của ứng dụng hoặc sự không ổn định của toàn bộ hệ điều hành.

- Các vấn đề nghiêm trọng có thể xảy ra khi không đóng **socket** làm cho việc **closing** là một hoạt động rất quan trọng.

- Sự khác biệt chính giữa việc tắt và đóng một **socket** TCP là việc đóng sẽ làm gián đoạn kết nối nếu một cổng được thiết lập và cuối cùng, xử lý **socket** và đưa nó trở lại hệ điều hành, trong khi việc tắt chỉ vô hiệu hóa việc ghi, đọc hoặc cả hai hoạt động trên **socket** và gửi một tin nhắn dịch vụ đến ứng dụng ngang hàng thông báo về thực tế này. Tắt **socket** không bao giờ dẫn đến việc phân bổ **socket**.

### The client application

- Mục đích của ứng dụng khách là cấp phát **socket** và kết nối nó với ứng dụng máy chủ. Sau khi kết nối được thiết lập, ứng dụng sẽ chuẩn bị và gửi một thông báo yêu cầu thông báo ranh giới của nó bằng cách tắt **socket** sau khi viết thông báo cho nó.

- Sau khi yêu cầu được gửi, ứng dụng khách sẽ đọc phản hồi. Kích thước của phản hồi là không xác định; do đó, việc đọc phải được thực hiện cho đến khi máy chủ đóng **socket** của nó để thông báo ranh giới phản hồi.

[**CODE**](asio-example/chapter-2/SockShutdownClient.cpp)

### The server application

- Ứng dụng máy chủ nhằm cấp phát một **socket** bộ nhận và chờ một yêu cầu kết nối một cách thụ động. Khi yêu cầu kết nối đến, nó sẽ chấp nhận nó và đọc dữ liệu từ **socket** được kết nối với máy khách cho đến khi ứng dụng khách tắt **socket** ở phía bên của nó. Sau khi nhận được thông báo yêu cầu, ứng dụng máy chủ sẽ gửi thông báo phản hồi thông báo ranh giới của nó bằng cách tắt **socket**.

[**CODE**](asio-example/chapter-2/SockShutdownServer.cpp)

### Closing a socket

- Để đóng một **socket** được cấp phát, phương thức `close()` phải được gọi trên đối tượng tương ứng của lớp `asio::ip::tcp::socket`. Tuy nhiên, thông thường, không cần phải làm điều đó một cách rõ ràng vì trình hủy của đối tượng socket sẽ đóng socket nếu một đối tượng không được đóng một cách rõ ràng.

---
